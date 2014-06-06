
#pragma once
#include "Window.h"
#include <windows.h>

namespace Judy
{
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
}
