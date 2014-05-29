
#pragma once
#include "Window.h"
#include <windows.h>

class WinWindow : Window
{
public:
    WinWindow();

    virtual void SetContext();
    virtual void Swap();

private:
    HWND hwnd;
    HDC hDC;
};
