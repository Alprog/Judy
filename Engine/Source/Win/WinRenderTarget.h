
#pragma once

#include "RenderTarget.h"
#include <windows.h>

class WinRenderTarget : RenderTarget
{
public:
    WinRenderTarget(HWND hWnd);

    HWND hWnd;
};
