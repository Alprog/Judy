
#pragma once

#include "Renderer.h"

#include <windows.h>

#include <d3d11.h>


class DXRenderer : Renderer
{
public:

    DXRenderer();

    void Render(Scene* scene, HWND hWnd);
    void Render(Scene* scene, SwapChain* context) override;


    void Clear(Color color) override;

    void SetTexture(std::wstring name);

private:
    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;

};

