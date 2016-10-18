
#pragma once

#include "Render/RenderTarget.h"
#include <windows.h>

class WinRenderTarget : public RenderTarget
{
public:
    WinRenderTarget(HINSTANCE hInstance, HWND hWnd);
    virtual Vector2 getSize() const override;

    HINSTANCE hInstance;
    HWND hWnd;
};

using PlatformRenderTarget = WinRenderTarget;
