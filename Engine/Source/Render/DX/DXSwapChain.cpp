
#include "DXSwapChain.h"
#include <DXRenderer.h>
#include <PlatformRenderTarget.h>

DXSwapChain::DXSwapChain(DXRenderer* renderer, RenderTarget* renderTarget)
    : renderer {renderer}
    , SwapChain {renderTarget}
{
    ComPtr<IDXGIFactory4> factory;
    auto result = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
    if (FAILED(result)) throw;

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = 2;

    auto size = renderTarget->getSize();
    swapChainDesc.Width = static_cast<unsigned int>(size.x);
    swapChainDesc.Height = static_cast<unsigned int>(size.y);
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;

    auto hwnd = static_cast<PlatformRenderTarget*>(renderTarget)->hWndEx;
    auto device = renderer->getDevice();
    auto commandQueue = renderer->getCommandQueue();

    ComPtr<IDXGISwapChain1> swapChain1;
    result = factory->CreateSwapChainForHwnd(commandQueue, hwnd, &swapChainDesc, nullptr, nullptr, &swapChain1);
    if (FAILED(result)) throw;

    result = factory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);
    if (FAILED(result)) throw;

    swapChain1.As(&swapChain);

    frameIndex = swapChain->GetCurrentBackBufferIndex();

    auto rtvHeapStart = renderer->getRtvHeap()->GetCPUDescriptorHandleForHeapStart();
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeapStart);
    for (UINT n = 0; n < 2; n++)
    {
        auto result = swapChain->GetBuffer(n, IID_PPV_ARGS(&renderTargets[n]));
        if (FAILED(result)) throw;
        device->CreateRenderTargetView(renderTargets[n].Get(), nullptr, rtvHandle);
        rtvHandle.Offset(1, renderer->getRtvDescriptorSize());
    }

    CD3DX12_RESOURCE_DESC resourceDesc(
        D3D12_RESOURCE_DIMENSION_TEXTURE2D, 0,
        static_cast<UINT>(size.x),
        static_cast<UINT>(size.y),
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

    auto dsvHeapStart = renderer->getDsvHeap()->GetCPUDescriptorHandleForHeapStart();
    device->CreateDepthStencilView(depthStencil.Get(), nullptr, dsvHeapStart);
}

void DXSwapChain::refreshSize()
{

}

void DXSwapChain::beginRenderFrame(ID3D12GraphicsCommandList* commandList)
{
    frameIndex = swapChain->GetCurrentBackBufferIndex();

    auto frame = renderTargets[frameIndex].Get();
    auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(frame, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    commandList->ResourceBarrier(1, &barrier);
}

void DXSwapChain::clear(ID3D12GraphicsCommandList* commandList)
{
    auto rtvHeapStart = renderer->getRtvHeap()->GetCPUDescriptorHandleForHeapStart();
    auto dsvHeapStart = renderer->getDsvHeap()->GetCPUDescriptorHandleForHeapStart();
    auto rtvDescriptorSize = renderer->getRtvDescriptorSize();

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeapStart, frameIndex, rtvDescriptorSize);
    CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(dsvHeapStart);
    commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

    const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
    commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
    commandList->ClearDepthStencilView(dsvHeapStart, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void DXSwapChain::endRenderFrame(ID3D12GraphicsCommandList* commandList)
{
    auto frame = renderTargets[frameIndex].Get();
    auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(frame, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
    commandList->ResourceBarrier(1, &barrier);
}

void DXSwapChain::present()
{
    auto result = swapChain->Present(0, 0);
    if (FAILED(result))
    {
        throw;
    }
}
