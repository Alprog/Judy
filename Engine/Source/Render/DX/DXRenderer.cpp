
#include "DXRenderer.h"
#include <PlatformRenderTarget.h>
#include <ShaderManager.h>

#include "DXShaderImpl.h"
#include "DXTextureImpl.h"
#include "Images.h"

#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../Shader.h"
#include "../Texture.h"
#include "../ConstantBuffer.h"
#include "DXConstantBufferImpl.h"
#include "DXDescriptorHeap.h"

DXRenderer::DXRenderer()
{
    init();
}

DXRenderer::~DXRenderer()
{
}

D3D12_VIEWPORT viewport;
D3D12_RECT scissorRect;

void DXRenderer::init()
{
    enableDebugLayer();
    createDevice();
    createCommandQueue();
    createDescriptorHeap();
    createCommandAllocator();
    createCommandListAndFence();
}

void DXRenderer::enableDebugLayer()
{
    ComPtr<ID3D12Debug> debugController;
    auto result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
    if (SUCCEEDED(result))
    {
        debugController->EnableDebugLayer();
    }
}

void DXRenderer::createDevice()
{
    ComPtr<IDXGIFactory4> factory;
    auto result = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
    if (FAILED(result)) throw;

    ComPtr<IDXGIAdapter1> adapter;
    for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != factory.Get()->EnumAdapters1(adapterIndex, &adapter); adapterIndex++)
    {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);

        if ((desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0)
        {
            auto result = D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr);
            if (SUCCEEDED(result))
            {
                break;
            }
        }
    }

    ComPtr<IDXGIAdapter1> hardwareAdapter;
    hardwareAdapter = adapter.Detach();

    result = D3D12CreateDevice(hardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));
    if (FAILED(result)) throw;
}

void DXRenderer::createCommandQueue()
{
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    auto result = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));
    if (FAILED(result)) throw;
}

void DXRenderer::createDescriptorHeap()
{
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = 2;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    auto result = device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
    if (FAILED(result)) throw;

    rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    //-----------

    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
    dsvHeapDesc.NumDescriptors = 1;
    dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    result = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));
    if (FAILED(result)) throw;

    //-----------

    srvCbvHeap = new DXDescriptorHeap(device.Get(), 10);
}

void DXRenderer::createCommandListAndFence()
{
    auto result = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList));
    if (FAILED(result)) throw;

    result = commandList->Close();
    if (FAILED(result)) throw;

    result = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
    if (FAILED(result)) throw;

    fenceValue = 1;
    fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

DXSwapChain* DXRenderer::getSwapChain(RenderTarget* renderTarget)
{
    auto it = swapChains.find(renderTarget);
    if (it != std::end(swapChains))
    {
        return it->second;
    }
    else
    {
        auto swapChain = new DXSwapChain(this, renderTarget);
        swapChains[renderTarget] = swapChain;
        return swapChain;
    }
}

void DXRenderer::createCommandAllocator()
{
    auto result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
    if (FAILED(result)) throw;
}

void DXRenderer::clear(Color color)
{

}

void DXRenderer::draw(RenderCommand renderCommand)
{
    auto mesh = renderCommand.mesh;
    auto texture = renderCommand.state->texture;
    auto cbImpl = getImpl(renderCommand.state->constantBuffer);
    cbImpl->update();

    commandList->SetGraphicsRootDescriptorTable(0, getImpl(texture)->descriptorHandle.getGPU());
    commandList->SetGraphicsRootDescriptorTable(1, cbImpl->descriptorHandle.getGPU());

    commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    commandList->IASetVertexBuffers(0, 1, &getImpl(mesh->vertexBuffer)->vertexBufferView);
    commandList->IASetIndexBuffer(&getImpl(mesh->indexBuffer)->indexBufferView);

    commandList->DrawIndexedInstanced(36, 1, 0, 0, 0);
}

void DXRenderer::waitForPreviousFrame()
{
    auto result = commandQueue->Signal(fence.Get(), fenceValue);
    if (FAILED(result)) throw;

    if (fence->GetCompletedValue() < fenceValue)
    {
        result = fence->SetEventOnCompletion(fenceValue, fenceEvent);
        if (FAILED(result)) throw;
        WaitForSingleObject(fenceEvent, INFINITE);
    }

    fenceValue++;
}

void DXRenderer::render(std::vector<RenderCommand> commands, RenderTarget* renderTarget)
{
    auto result = commandAllocator->Reset();
    if (FAILED(result)) throw;

    auto& firstCommand = commands[0];

    auto pso = getImpl(firstCommand.state->getPipelineState());

    result = commandList->Reset(commandAllocator.Get(), pso->pipelineState.Get());
    if (FAILED(result)) throw;

    commandList->SetGraphicsRootSignature(pso->rootSignature.Get());

    ID3D12DescriptorHeap* ppHeaps[] = { srvCbvHeap->get() };
    commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

    auto rtSize = renderTarget->getSize();
    viewport.Width = static_cast<float>(rtSize.x);
    viewport.Height = static_cast<float>(rtSize.y);
    viewport.MaxDepth = 1.0f;
    commandList->RSSetViewports(1, &viewport);

    scissorRect.right = static_cast<LONG>(rtSize.x);
    scissorRect.bottom = static_cast<LONG>(rtSize.y);
    commandList->RSSetScissorRects(1, &scissorRect);

    auto swapChain = getSwapChain(renderTarget);
    swapChain->refreshSize();
    swapChain->beginRenderFrame(commandList.Get());
    swapChain->clear(commandList.Get());

    for (auto& command : commands)
    {
        draw(command);
    }

    swapChain->endRenderFrame(commandList.Get());

    result = commandList->Close();
    if (FAILED(result)) throw;

    ID3D12CommandList* ppCommandLists[] = { commandList.Get() };
    commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

    swapChain->present();

    waitForPreviousFrame();
}
