
#include "WinWindow.h"
#include "App.h"

#include <windows.h>

Window* currentEventWindow = NULL;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
        // this message is read when the window is closed
        case WM_CREATE:
            printf("create!");
            fflush(stdout);
            break;

        case WM_QUIT:
            printf("quit!");
            fflush(stdout);
            break;

        case WM_CLOSE:
            printf("close!");
            fflush(stdout);
            break;

        case WM_DESTROY:
            App::Instance()->RemoveWindow(currentEventWindow);

            break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
}

WinWindow::WinWindow()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    LPCWSTR className = L"MyClass";

    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = className;
    RegisterClassEx(&wc);

    DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SYSMENU;

    currentEventWindow = this;
    hWnd = CreateWindowEx(NULL, className, L"A Real Win App", dwStyle,
                          100, 100, 400, 400, NULL, NULL, hInstance, NULL);
    currentEventWindow = NULL;

    App::Instance()->AddWindow(this);
}

void SetupPixelFormat(HDC hDC)
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

HGLRC hRC;
bool a = false;

void WinWindow::ProcessEvents()
{
    MSG msg;
    currentEventWindow = this;
    PeekMessage(&msg, hWnd, NULL, NULL, PM_REMOVE);
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    currentEventWindow = NULL;
}

void WinWindow::SetContext()
{
    hDC = GetDC(hWnd);
    SetupPixelFormat(hDC);

    if (!a)
    {
        hRC = wglCreateContext(hDC);
        a = true;
    }

    wglMakeCurrent(hDC, hRC);
}

void WinWindow::Swap()
{
    SwapBuffers(hDC);
}
