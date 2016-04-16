
#pragma once

#include "Render/GL/GLContext.h"
#include <windows.h>

class WinGLContext : GLContext
{
public:
    WinGLContext(HWND hWnd);

    virtual void MakeCurrent() override;
    virtual void Swap() override;

private:
    void SetupPixelFormat(HDC hDC);

    static HGLRC hRC; // render context
    HDC hDC;          // device context
};
