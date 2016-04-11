
#pragma once

#include "../Renderer.h"
#include "../RendererBase.h"

#include <windows.h>

#include "dx.h"

#include <dxgi1_4.h>
#include <unordered_map>

#include "DXVertexBufferImpl.h"
#include "DXShaderImpl.h"
#include "DXIndexBufferImpl.h"
#include "DXTextureImpl.h"
#include "DXConstantBufferImpl.h"

class Texture;
class Shader;
class ConstantBuffer;

class DXRenderer : public RendererBase<DXRenderer>
{
public:
    static const RendererType rendererType = RendererType::DX;

    DXRenderer();
    virtual ~DXRenderer();

    virtual void Draw(Mesh* mesh, Matrix matrix, RenderState* renderState) override;
    virtual void DrawQuad(Quad* quad) override;
    virtual void Render(Node* scene, RenderTarget* renderTarget) override;

    void Init();
    void EnableDebugLayer();
    void CreateDevice();
    void CreateCommandQueue();
    void CreateDescriptorHeap();
    void CreateCommandAllocator();
    void CreateCommandListAndFence();
    void PopulateCommandList(Node* scene);
    void WaitForPreviousFrame();

    ComPtr<IDXGISwapChain3> GetSwapChain(RenderTarget* renderTarget);
    ComPtr<IDXGISwapChain3> CreateSwapChain(HWND hwnd, int width, int height);

    void Clear(Color color) override;

    inline ID3D12Device* GetDevice() { return device.Get(); }
    inline ID3D12GraphicsCommandList* GetCommandList() { return commandList.Get(); }
    inline ID3D12DescriptorHeap* GetSrvCbvHeap() { return srvCbvHeap.Get(); }

    inline ID3D12CommandAllocator* GetCommandAllocator() { return commandAllocator.Get(); }
    inline ID3D12CommandQueue* GetCommandQueue() { return commandQueue.Get(); }
    inline UINT GetSrvCbvDescriptorSize() { return srvCbvDescriptorSize; }
private:
    ComPtr<ID3D12Device> device;
    ComPtr<ID3D12CommandQueue> commandQueue;
    ComPtr<ID3D12DescriptorHeap> rtvHeap;
    ComPtr<ID3D12DescriptorHeap> srvCbvHeap;
    ComPtr<ID3D12CommandAllocator> commandAllocator;
    ComPtr<ID3D12Resource> renderTargets[2];
    UINT rtvDescriptorSize;
    UINT srvCbvDescriptorSize;

    ComPtr<ID3D12GraphicsCommandList> commandList;
    UINT frameIndex;
    HANDLE fenceEvent;
    ComPtr<ID3D12Fence> fence;
    UINT64 fenceValue;

    std::unordered_map<RenderTarget*, ComPtr<IDXGISwapChain3>> swapChains;

    void InitQuad();
};
