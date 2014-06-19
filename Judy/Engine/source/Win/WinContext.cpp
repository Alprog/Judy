
#include "WinContext.h"

HGLRC WinContext::hRC = nullptr;

WinContext::WinContext(HWND hWnd)
{
    hDC = GetDC(hWnd);
    SetupPixelFormat(hDC);
    if (hRC == nullptr)
    {
        hRC = wglCreateContext(hDC);
    }
}

void WinContext::MakeCurrent()
{
    wglMakeCurrent(hDC, hRC);
}

void WinContext::Swap()
{
     SwapBuffers(hDC);
}

void WinContext::SetupPixelFormat(HDC hDC)
{
    int nPixelFormat;

    static PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),          //size of structure
        1,                                      //default version
        PFD_DRAW_TO_WINDOW |                    //window drawing support
        PFD_SUPPORT_OPENGL |                    //opengl support
        PFD_DOUBLEBUFFER,                       //double buffering support
        PFD_TYPE_RGBA,                          //RGBA color mode
        32,                                     //32 bit color mode
        0, 0, 0, 0, 0, 0,                       //ignore color bits
        0,                                      //no alpha buffer
        0,                                      //ignore shift bit
        0,                                      //no accumulation buffer
        0, 0, 0, 0,                             //ignore accumulation bits
        16,                                     //16 bit z-buffer size
        0,                                      //no stencil buffer
        0,                                      //no aux buffer
        PFD_MAIN_PLANE,                         //main drawing plane
        0,                                      //reserved
        0, 0, 0                                 //layer masks ignored
    };

    nPixelFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, nPixelFormat, &pfd);
}
