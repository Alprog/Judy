
#pragma once

#include "Render/GL/GLContext.h"
#include "Render/RenderTarget.h"
#include <windows.h>

class WinGLContext : public GLContext
{
public:
    WinGLContext(HWND hWnd = 0);
    WinGLContext(RenderTarget* renderTarget);

    virtual void MakeCurrent() override;
    virtual void Swap() override;

private:
    void SetupPixelFormat(HDC hDC);

    static HGLRC hRC; // render context
    HDC hDC;          // device context
};

using PlatformGLContext = WinGLContext;
