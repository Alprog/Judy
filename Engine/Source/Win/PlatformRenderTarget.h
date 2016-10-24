
#pragma once

#include <RenderTarget.h>
#include <windows.h>

class WinRenderTarget : public RenderTarget
{
public:
    WinRenderTarget(HINSTANCE hInstance, HWND hWnd);

    virtual void onRendering(RendererType type) override;
    virtual Vector2 getSize() const override;

    HINSTANCE hInstance;
    HWND hWnd;

    // mix DX- and GL/Vulkan-render causes problems
    // use additional hWnd for DX
    HWND hWndEx;
};

using PlatformRenderTarget = WinRenderTarget;
