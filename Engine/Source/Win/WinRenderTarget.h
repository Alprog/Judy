
#pragma once

#include "RenderTarget.h"
#include <windows.h>

class WinRenderTarget : public RenderTarget
{
public:
    WinRenderTarget(HWND hWnd);

    HWND hWnd;
};
