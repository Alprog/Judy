
#pragma once

#include "SwapChain.h"

#include "DXRenderer.h"
#include <DXGI1_2.h>

class DXSwapChain : SwapChain
{
public:
    DXSwapChain(DXRenderer* renderer, HWND hWnd);

    virtual void MakeCurrent() override;
    virtual void Swap() override;


    ID3D11RenderTargetView* view = nullptr;
private:
    IDXGISwapChain1* swapChain = nullptr;

};
