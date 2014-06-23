
#pragma once
#include "Window.h"
#include <windows.h>

class WinWindow : Window
{
public:
    WinWindow();
    ~WinWindow();

    virtual void ProcessEvents() override;

    HWND hWnd;

    HWND hWnd1;
    HWND hWnd2;

private:

    HDC hDC;
};
