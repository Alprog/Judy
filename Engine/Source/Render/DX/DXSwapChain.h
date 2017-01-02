
#pragma once

#include <SwapChain.h>
#include <dx.h>
#include <dxgi1_4.h>

class DXRenderer;
class RenderTarget;

class DXSwapChain : public SwapChain
{
public:
    DXSwapChain(DXRenderer* renderer, RenderTarget* renderTarget);

    virtual void refreshSize() override;

    void beginRenderFrame(ID3D12GraphicsCommandList* commandList);
    void endRenderFrame(ID3D12GraphicsCommandList* commandList);
    void clear(ID3D12GraphicsCommandList* commandList);
    void present();

private:
    DXRenderer* renderer;
    ComPtr<IDXGISwapChain3> swapChain;
    ComPtr<ID3D12Resource> renderTargets[2];
    ComPtr<ID3D12Resource> depthStencil;
    UINT frameIndex;
};
