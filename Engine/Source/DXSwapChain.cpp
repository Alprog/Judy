
#include "DXSwapChain.h"
#include "Win/WinRenderTarget.h"

DXSwapChain::DXSwapChain(DXRenderer* renderer, RenderTarget* renderTarget)
{
    auto hWnd = ((WinRenderTarget*)renderTarget)->hWnd;

    DXGI_SWAP_CHAIN_DESC1 desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = 400;
    desc.Height = 800;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.Stereo = false;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.BufferCount = 2;
    desc.Scaling = DXGI_SCALING_NONE;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    IDXGIFactory2* factory;
    CreateDXGIFactory1(__uuidof(IDXGIFactory2), (void**)&factory);
    factory->CreateSwapChainForHwnd(renderer->device, hWnd, &desc, NULL, NULL, &swapChain);

    ID3D11Texture2D* backBuffer;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
    renderer->device->CreateRenderTargetView(backBuffer, NULL, &view);
}
