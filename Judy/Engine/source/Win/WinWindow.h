
#pragma once
#include "Window.h"
#include <windows.h>

class WinWindow : Window
{
public:
    WinWindow();
    ~WinWindow();

    virtual void ProcessEvents() override;

private:
    HWND hWnd;
    HDC hDC;
};
