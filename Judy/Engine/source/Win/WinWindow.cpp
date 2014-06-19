
#include "WinWindow.h"

#include "App.h"
#include "WinContext.h"

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

    context = (Context*)new WinContext(hWnd);
}

WinWindow::~WinWindow()
{
    delete context;
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
