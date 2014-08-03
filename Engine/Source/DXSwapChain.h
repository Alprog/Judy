
#pragma once

#include "DXRenderer.h"
#include <DXGI1_2.h>

class DXSwapChain
{
public:
    DXSwapChain(DXRenderer* renderer, RenderTarget* renderTarget);

    IDXGISwapChain1* swapChain = nullptr;
    ID3D11RenderTargetView* view = nullptr;

};
