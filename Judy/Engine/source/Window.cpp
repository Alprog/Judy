#include "Window.h"

#include "App.h"
#include <stdio.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
        // this message is read when the window is closed
        case WM_CREATE:
            App::Instance()->WindowCount++;
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
            App::Instance()->WindowCount--;

            printf("destroy!");
            fflush(stdout);

            // close the application entirely
            PostQuitMessage(0);
            return 0;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
}

Window::Window()
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

    hwnd = CreateWindowEx(NULL, className, L"A Real Win App", dwStyle,
                          100, 100, 400, 400, NULL, NULL, hInstance, NULL);


    //bool a = ShowWindow(hwnd, 0);
    //printf(a ? "YES!!!" : "NO!!!");
}

void Window::show()
{

}
