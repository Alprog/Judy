
#pragma once

#include "Window.h"
#include "WinRenderTarget.h"
#include <windows.h>

class WinWindow : public WindowM
{
public:
    WinWindow();
    ~WinWindow();

    virtual void ProcessEvents() override;
    virtual void Render() override;

    HWND hWnd;

private:

    HDC hDC;
};
