
#pragma once

#include "../IRenderer.h"

#include <windows.h>

#include "dx.h"

#include <dxgi1_4.h>
#include <unordered_map>

#include "DXVertexBufferImpl.h"
#include "DXShaderImpl.h"
#include "DXIndexBufferImpl.h"
#include "DXTextureImpl.h"
#include "DXConstantBufferImpl.h"
#include "../Renderer.h"

class Texture;
class Shader;
class ConstantBuffer;
class DXDescriptorHeap;

class DXRenderer : public Renderer<RendererType::DX>
{
public:
    DXRenderer();
    virtual ~DXRenderer();

    virtual void Render(std::vector<RenderCommand> commands, RenderTarget* target) override;
    virtual void Draw(RenderCommand renderCommand) override;

    void Init();
    void EnableDebugLayer();
    void CreateDevice();
    void CreateCommandQueue();
    void CreateDescriptorHeap();
    void CreateCommandAllocator();
    void CreateCommandListAndFence();
    void PopulateCommandList(std::vector<RenderCommand> commands);
    void WaitForPreviousFrame();

    ComPtr<IDXGISwapChain3> GetSwapChain(RenderTarget* renderTarget);
    ComPtr<IDXGISwapChain3> CreateSwapChain(HWND hwnd, int width, int height);

    void Clear(Color color) override;

    inline ID3D12Device* GetDevice() { return device.Get(); }
    inline ID3D12GraphicsCommandList* GetCommandList() { return commandList.Get(); }
    inline DXDescriptorHeap* GetSrvCbvHeap() { return srvCbvHeap; }

    inline ID3D12CommandAllocator* GetCommandAllocator() { return commandAllocator.Get(); }
    inline ID3D12CommandQueue* GetCommandQueue() { return commandQueue.Get(); }

private:
    ComPtr<ID3D12Device> device;
    ComPtr<ID3D12CommandQueue> commandQueue;
    ComPtr<ID3D12DescriptorHeap> rtvHeap;
    ComPtr<ID3D12DescriptorHeap> dsvHeap;
    DXDescriptorHeap* srvCbvHeap;
    ComPtr<ID3D12CommandAllocator> commandAllocator;
    ComPtr<ID3D12Resource> renderTargets[2];
    ComPtr<ID3D12Resource> depthStencil;
    UINT rtvDescriptorSize;

    ComPtr<ID3D12GraphicsCommandList> commandList;
    UINT frameIndex;
    HANDLE fenceEvent;
    ComPtr<ID3D12Fence> fence;
    UINT64 fenceValue;

    std::unordered_map<RenderTarget*, ComPtr<IDXGISwapChain3>> swapChains;

    void InitQuad();
};