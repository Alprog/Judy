
#include "WinRenderTarget.h"

WinRenderTarget::WinRenderTarget(HWND hWnd)
{
    this->hWnd = hWnd;
}

Vector2 WinRenderTarget::GetSize() const
{
    RECT rect;
    GetWindowRect(hWnd, &rect);
    return Vector2(rect.right - rect.left, rect.bottom - rect.top);
}
