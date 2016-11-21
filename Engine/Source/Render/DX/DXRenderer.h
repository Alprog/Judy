
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
#include "DXPipelineStateImpl.h"
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

    virtual void render(std::vector<RenderCommand> commands, RenderTarget* target) override;
    virtual void draw(RenderCommand renderCommand) override;

    void init();
    void enableDebugLayer();
    void createDevice();
    void createCommandQueue();
    void createDescriptorHeap();
    void createCommandAllocator();
    void createCommandListAndFence();
    void populateCommandList(std::vector<RenderCommand> commands);
    void waitForPreviousFrame();

    ComPtr<IDXGISwapChain3> getSwapChain(RenderTarget* renderTarget);
    ComPtr<IDXGISwapChain3> createSwapChain(HWND hwnd, int width, int height);

    void clear(Color color) override;

    inline ID3D12Device* getDevice() { return device.Get(); }
    inline ID3D12GraphicsCommandList* getCommandList() { return commandList.Get(); }
    inline DXDescriptorHeap* getSrvCbvHeap() { return srvCbvHeap; }

    inline ID3D12CommandAllocator* getCommandAllocator() { return commandAllocator.Get(); }
    inline ID3D12CommandQueue* getCommandQueue() { return commandQueue.Get(); }

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
