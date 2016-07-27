
#include "InputSystem.h"

LRESULT CALLBACK InputWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INPUT:
            printf("input");
            break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

InputSystem::InputSystem()
{
    auto hInstance = GetModuleHandle(nullptr);
    LPCWSTR className = L"InputWindow";

    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = InputWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(0, className, 0, 0, 0, 0, 0, 0, nullptr, nullptr, hInstance, nullptr);

    RAWINPUTDEVICE Rid[2];

    Rid[0].usUsagePage = 0x01;
    Rid[0].usUsage = 0x06;
    Rid[0].dwFlags = RIDEV_INPUTSINK;
    Rid[0].hwndTarget = hWnd;

    Rid[1].usUsagePage = 0x01;
    Rid[1].usUsage = 0x02;
    Rid[1].dwFlags = RIDEV_INPUTSINK;
    Rid[1].hwndTarget = hWnd;

    bool result = RegisterRawInputDevices(Rid, 2, sizeof(RAWINPUTDEVICE));
    result = true;
}

void InputSystem::UpdateState()
{
    MSG msg;
    PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE);
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}
