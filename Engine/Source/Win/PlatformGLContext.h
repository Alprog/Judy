
#pragma once

#include "Render/GL/GLContext.h"
#include "Render/RenderTarget.h"
#include <windows.h>

class WinGLContext : public GLContext
{
public:
    WinGLContext(HWND hWnd = 0);
    WinGLContext(RenderTarget* renderTarget);

    virtual void makeCurrent() override;
    virtual void swap() override;

private:
    void setupPixelFormat(HDC hDC);

    static HGLRC hRC; // render context
    HDC hDC;          // device context
};

using PlatformGLContext = WinGLContext;
