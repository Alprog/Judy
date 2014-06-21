
#include "DXRenderer.h"

#include <d3d11.h>
#include <DXGI.h>

#include <stdio.h>

ID3D11Device* device = nullptr;
ID3D11DeviceContext* deviceContext = nullptr;
IDXGISwapChain* swapChain = nullptr;
ID3D11RenderTargetView* view = nullptr;

DXRenderer::DXRenderer()
{
    auto type = D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE;

    auto featureLevels = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
    D3D_FEATURE_LEVEL featureLevel;

    HRESULT a = D3D11CreateDevice(NULL, type, NULL, 0, &featureLevels, 1, D3D11_SDK_VERSION, &device, &featureLevel, &deviceContext);

    printf("%i", a);
    fflush(stdout);
}

void DXRenderer::Render(Scene* scene, HWND hWnd)
{
    if (!swapChain)
    {
        DXGI_SWAP_CHAIN_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.BufferCount = 1;
        desc.BufferDesc.Width = 640;
        desc.BufferDesc.Height = 480;
        desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.BufferDesc.RefreshRate.Numerator = 60;
        desc.BufferDesc.RefreshRate.Denominator = 1;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.OutputWindow = hWnd;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Windowed = TRUE;

        IDXGIFactory* factory;
        CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
        factory->CreateSwapChain(device, &desc, &swapChain);

        ID3D11Texture2D* backBuffer;
        swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
        device->CreateRenderTargetView(backBuffer, NULL, &view);
    }

    deviceContext->OMSetRenderTargets(1, &view, NULL);

    float color[4];
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    color[3] = 0;

    deviceContext->ClearRenderTargetView(view, color);

    swapChain->Present(0, 0);

}

void DXRenderer::Render(Scene *scene, Context *context)
{

}
