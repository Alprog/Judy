
#pragma once
#include "Window.h"
#include <windows.h>

class WinWindow : Window
{
public:
    WinWindow();

private:
    HWND hwnd;
};
