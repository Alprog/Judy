
#pragma once

#include "Window.h"
#include <PlatformRenderTarget.h>
#include <windows.h>

class WinWindow : public Window
{
public:
    WinWindow();
    ~WinWindow();

    virtual void processEvents() override;

    HWND hWnd;
    HWND hWnd1;
    HWND hWnd2;

    virtual void switchRenderType() override;

private:
    HDC hDC;

    RenderTarget* renderTarget1;
    RenderTarget* renderTarget2;
};

using PlatformWindow = WinWindow;
