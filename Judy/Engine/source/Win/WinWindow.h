
#pragma once
#include "Window.h"
#include <windows.h>

using namespace Judy;

namespace Judy
{
    class WinWindow : JWindow
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
