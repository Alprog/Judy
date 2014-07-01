
#pragma once

#include "Renderer.h"

#include <windows.h>

class DXRenderer : Renderer
{
public:

    DXRenderer();

    void Render(Scene* scene, HWND hWnd);
    void Render(Scene* scene, SwapChain* context) override;

    void Clear(Color color) override;
};
