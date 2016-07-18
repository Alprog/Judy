
#include "WinRenderTarget.h"

WinRenderTarget::WinRenderTarget(HINSTANCE hInstance, HWND hWnd)
{
    this->hInstance = hInstance;
    this->hWnd = hWnd;
}

Vector2 WinRenderTarget::GetSize() const
{
    RECT rect;
    GetClientRect(hWnd, &rect);
    return Vector2(rect.right - rect.left, rect.bottom - rect.top);
}
