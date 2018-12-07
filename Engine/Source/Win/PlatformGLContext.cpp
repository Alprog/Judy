
#include <PlatformGLContext.h>
#include <PlatformRenderTarget.h>

HGLRC WinGLContext::hRC = nullptr;

WinGLContext::WinGLContext(RenderTarget* renderTarget)
    : WinGLContext(static_cast<WinRenderTarget*>(renderTarget)->hWnd)
{
}

WinGLContext::WinGLContext(HWND hWnd)
{
    hDC = GetDC(hWnd);

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
        24,                                     //16 bit z-buffer size
        0,                                      //no stencil buffer
        0,                                      //no aux buffer
        PFD_MAIN_PLANE,                         //main drawing plane
        0,                                      //reserved
        0, 0, 0                                 //layer masks ignored
    };

    int current = GetPixelFormat(hDC);
    printf("%i\n", current);

    int nPixelFormat = ChoosePixelFormat(hDC, &pfd);

    DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    if (SetPixelFormat(hDC, nPixelFormat, &pfd) == FALSE)
    {
        auto l = GetLastError();
        printf("error opengl %lu\n", l);
        fflush(stdout);
        exit(0);
    }

    if (hRC == nullptr)
    {
        hRC = wglCreateContext(hDC);
    }
}

void WinGLContext::makeCurrent()
{
    wglMakeCurrent(hDC, hRC);
}

void WinGLContext::swap()
{
    SwapBuffers(hDC);
}

void WinGLContext::setupPixelFormat(HDC hDC)
{

}
