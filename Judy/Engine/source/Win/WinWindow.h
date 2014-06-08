
#pragma once
#include "Window.h"
#include <windows.h>

class WinWindow : Window
{
public:
    WinWindow();

    virtual void ProcessEvents();

    virtual void SetContext();
    virtual void Swap();

private:
    HWND hWnd;
    HDC hDC;
};
