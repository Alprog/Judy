
#pragma once

#include <windows.h>
#include "Context.h"

class WinContext : SwapChain
{
public:
    WinContext(HWND hWnd);

    virtual void MakeCurrent() override;
    virtual void Swap() override;

private:
    void SetupPixelFormat(HDC hDC);

    static HGLRC hRC; // render context
    HDC hDC;          // device context
};
