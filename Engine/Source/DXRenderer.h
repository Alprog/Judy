
#pragma once

#include "Renderer.h"

#include <windows.h>

#include "dx.h"

#include <dxgi1_4.h>
#include <unordered_map>

#include "DXSwapChain.h"

class Image;
class Shader;

class DXRenderer : public Renderer
{
public:
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
    void PopulateCommandList();
    void WaitForPreviousFrame();

    ComPtr<IDXGISwapChain3> GetSwapChain(RenderTarget* renderTarget);
    ComPtr<IDXGISwapChain3> CreateSwapChain(HWND hwnd, int width, int height);

    void Clear(Color color) override;

    inline ID3D12Device* GetDevice() { return device.Get(); }
    inline ID3D12GraphicsCommandList* GetCommandList() { return commandList.Get(); }
    inline ID3D12DescriptorHeap* GetSRVHeap() { return srvHeap.Get(); }

    inline ID3D12CommandAllocator* GetCommandAllocator() { return commandAllocator.Get(); }
    inline ID3D12CommandQueue* GetCommandQueue() { return commandQueue.Get(); }

    virtual void* CreateTexture(Image* image) override;
    virtual void* CreateShader(Shader* shader) override;

private:
    ComPtr<ID3D12Device> device;
    ComPtr<ID3D12CommandQueue> commandQueue;
    ComPtr<ID3D12DescriptorHeap> rtvHeap;
    ComPtr<ID3D12DescriptorHeap> srvHeap;
    ComPtr<ID3D12CommandAllocator> commandAllocator;
    ComPtr<ID3D12Resource> renderTargets[2];
    UINT rtvDescriptorSize;

    ComPtr<ID3D12GraphicsCommandList> commandList;
    UINT frameIndex;
    HANDLE fenceEvent;
    ComPtr<ID3D12Fence> fence;
    UINT64 fenceValue;

    std::unordered_map<RenderTarget*, ComPtr<IDXGISwapChain3>> swapChains;

    void InitQuad();

};

