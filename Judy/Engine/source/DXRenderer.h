
#pragma once

#include "Renderer.h"

#include <windows.h>

class DXRenderer : Renderer
{
public:

    DXRenderer();

    void Render(Scene* scene, HWND hWnd);

    void Render(Scene* scene, Context* context) override;
};

