
#include "WinWindow.h"

#include "App.h"
#include "WinGLContext.h"

#include <windows.h>

Window* currentEventWindow = NULL;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_CREATE:
            App::Instance()->AddWindow(currentEventWindow);
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
            delete currentEventWindow;

            break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}

WinWindow::WinWindow()
{
    SetProcessDPIAware();

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

    RECT rect = {0, 0, 800, 800};
    AdjustWindowRect(&rect, dwStyle, false);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    int x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

    auto title = L"Judy Window";
    hWnd = CreateWindowEx(NULL, className, title, dwStyle, x, y, width, height, NULL, NULL, hInstance, NULL);
    currentEventWindow = NULL;

    dwStyle = WS_CHILD | WS_VISIBLE;

    auto hWnd1 = CreateWindowEx(NULL, L"EDIT", L"", dwStyle, 0, 0, 400, 800, hWnd, NULL, hInstance, NULL);
    RenderTarget1 = (RenderTarget*)new WinRenderTarget(hWnd1);

    auto hWnd2 = CreateWindowEx(NULL, L"EDIT", L"", dwStyle, 400, 0, 400, 800, hWnd, NULL, hInstance, NULL);
    RenderTarget2 = (RenderTarget*)new WinRenderTarget(hWnd2);
}

WinWindow::~WinWindow()
{
}

void WinWindow::ProcessEvents()
{
    MSG msg;
    currentEventWindow = this;
    PeekMessage(&msg, hWnd, NULL, NULL, PM_REMOVE);
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    currentEventWindow = NULL;
}