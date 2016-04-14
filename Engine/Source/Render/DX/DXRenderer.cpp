
#include "DXRenderer.h"
#include "Win/WinRenderTarget.h"

#include <d3dx12.h>

#include "DXPipelineState.h"
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
    Init();
}

DXRenderer::~DXRenderer()
{
}

DXPipelineState* state = nullptr;
D3D12_VIEWPORT viewport;
D3D12_RECT scissorRect;

void DXRenderer::Init()
{
    EnableDebugLayer();
    CreateDevice();
    CreateCommandQueue();
    CreateDescriptorHeap();
    CreateCommandAllocator();
    CreateCommandListAndFence();
}

void DXRenderer::EnableDebugLayer()
{
    ComPtr<ID3D12Debug> debugController;
    auto result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
    if (SUCCEEDED(result))
    {
        debugController->EnableDebugLayer();
    }
}

void DXRenderer::CreateDevice()
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

void DXRenderer::CreateCommandQueue()
{
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    auto result = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));
    if (FAILED(result)) throw;
}

void DXRenderer::CreateDescriptorHeap()
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

void DXRenderer::CreateCommandListAndFence()
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

ComPtr<IDXGISwapChain3> DXRenderer::GetSwapChain(RenderTarget* renderTarget)
{
    auto it = swapChains.find(renderTarget);
    if (it != std::end(swapChains))
    {
        return it->second;
    }
    else
    {
        auto size = renderTarget->GetSize();
        auto hwnd = static_cast<WinRenderTarget*>(renderTarget)->hWnd;

        auto swapChain = CreateSwapChain(hwnd, size.x, size.y);
        swapChains[renderTarget] = swapChain;
        return swapChain;
    }
}

ComPtr<IDXGISwapChain3> DXRenderer::CreateSwapChain(HWND hwnd, int width, int height)
{
    ComPtr<IDXGIFactory4> factory;
    auto result = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
    if (FAILED(result)) throw;

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = 2;
    swapChainDesc.Width = (unsigned int)width;
    swapChainDesc.Height = (unsigned int)height;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;

    ComPtr<IDXGISwapChain1> swapChain1;
    result = factory->CreateSwapChainForHwnd(commandQueue.Get(), hwnd, &swapChainDesc, nullptr, nullptr, &swapChain1);
    if (FAILED(result)) throw;

    result = factory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);
    if (FAILED(result)) throw;

    ComPtr<IDXGISwapChain3> swapChain3;
    swapChain1.As(&swapChain3);

    frameIndex = swapChain3->GetCurrentBackBufferIndex();

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart());
    for (UINT n = 0; n < 2; n++)
    {
        auto result = swapChain3->GetBuffer(n, IID_PPV_ARGS(&renderTargets[n]));
        if (FAILED(result)) throw;
        device->CreateRenderTargetView(renderTargets[n].Get(), nullptr, rtvHandle);
        rtvHandle.Offset(1, rtvDescriptorSize);
    }

    CD3DX12_RESOURCE_DESC resourceDesc(
        D3D12_RESOURCE_DIMENSION_TEXTURE2D, 0,
        static_cast<UINT>(width),
        static_cast<UINT>(height),
        1, 1, DXGI_FORMAT_D32_FLOAT, 1, 0,
        D3D12_TEXTURE_LAYOUT_UNKNOWN,
        D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL | D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE);

    D3D12_CLEAR_VALUE clearValue;
    clearValue.Format = DXGI_FORMAT_D32_FLOAT;
    clearValue.DepthStencil.Depth = 1.0f;
    clearValue.DepthStencil.Stencil = 0;

    result = device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_DEPTH_WRITE,
        &clearValue,
        IID_PPV_ARGS(&depthStencil));
    if (FAILED(result)) throw;

    depthStencil->SetName(L"DepthStencil");

    device->CreateDepthStencilView(depthStencil.Get(), nullptr, dsvHeap->GetCPUDescriptorHandleForHeapStart());

    return swapChain3;
}

void DXRenderer::CreateCommandAllocator()
{
    auto result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
    if (FAILED(result)) throw;
}

void DXRenderer::Clear(Color color)
{

}

void DXRenderer::Draw(Mesh* mesh, Matrix matrix, RenderState* renderState)
{
    commandList->SetGraphicsRootDescriptorTable(0, renderState->texture->dxImpl->descriptorHandle.GetGPU());
    commandList->SetGraphicsRootDescriptorTable(1, renderState->constantBuffer->dxImpl->descriptorHandle.GetGPU());

    commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    commandList->IASetVertexBuffers(0, 1, &mesh->vertexBuffer->dxImpl->vertexBufferView);
    commandList->IASetIndexBuffer(&mesh->indexBuffer->dxImpl->indexBufferView);

    commandList->DrawIndexedInstanced(36, 1, 0, 0, 0);
}

void DXRenderer::DrawQuad(Quad* quad)
{

}

void DXRenderer::PopulateCommandList(Node* scene)
{
    auto result = commandAllocator->Reset();
    if (FAILED(result)) throw;

    if (state == nullptr)
    {
        auto vertexShader = new Shader("shadersTextured", Shader::Type::Vertex);
        auto pixelShader = new Shader("shadersTextured", Shader::Type::Pixel);
        state = new DXPipelineState(vertexShader, pixelShader, this);
    }

    result = commandList->Reset(commandAllocator.Get(), state->pipelineState.Get());
    if (FAILED(result)) throw;

    commandList->SetGraphicsRootSignature(state->rootSignature.Get());

    ID3D12DescriptorHeap* ppHeaps[] = { srvCbvHeap->Get() };
    commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);


    viewport.Width = static_cast<float>(800);
    viewport.Height = static_cast<float>(800);
    viewport.MaxDepth = 1.0f;
    commandList->RSSetViewports(1, &viewport);

    scissorRect.right = static_cast<LONG>(800);
    scissorRect.bottom = static_cast<LONG>(800);
    commandList->RSSetScissorRects(1, &scissorRect);

    commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(),
                                 D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, rtvDescriptorSize);
    CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(dsvHeap->GetCPUDescriptorHandleForHeapStart());
    commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

    const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
    commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
    commandList->ClearDepthStencilView(dsvHeap->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

    scene->Render(scene->transform.getMatrix(), this);

    commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(),
                                D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

    result = commandList->Close();
    if (FAILED(result)) throw;
}

void DXRenderer::WaitForPreviousFrame()
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

void DXRenderer::Render(Node* scene, RenderTarget* renderTarget)
{
    auto swapChain = GetSwapChain(renderTarget);

    PopulateCommandList(scene);

    ID3D12CommandList* ppCommandLists[] = { commandList.Get() };
    commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

    auto result = swapChain->Present(1, 0);
    if (FAILED(result)) throw;

    WaitForPreviousFrame();
    frameIndex = swapChain->GetCurrentBackBufferIndex();
}
