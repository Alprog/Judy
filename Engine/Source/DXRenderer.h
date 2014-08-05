
#pragma once

#include "Renderer.h"

#include <windows.h>
#include <d3d11.h>

#include "DXShaderResource.h"

class DXSwapChain;

class DXRenderer : Renderer
{
public:
    std::unordered_map<RenderTarget*, DXSwapChain*> swapChains;

    DXSwapChain* GetSwapChain(RenderTarget* renderTarget);

    DXRenderer();

    std::unordered_map<std::wstring, DXShaderResource*> shaders;

    void Render(Scene* scene, RenderTarget* renderTarget) override;

    void Clear(Color color) override;
    void SetTexture(std::wstring name);
    void SetShader(std::wstring name);

    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;

};

