
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

    virtual void setRenderer(IRenderer* renderer) override;
    virtual void switchRenderType() override;

private:
    HDC hDC;
};

using PlatformWindow = WinWindow;
