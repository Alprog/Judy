
#pragma once

#include "Window.h"
#include "WinRenderTarget.h"
#include <windows.h>

class WinWindow : public Window
{
public:
    WinWindow();
    ~WinWindow();

    virtual void ProcessEvents() override;

    HWND hWnd;

private:
    HDC hDC;
};
