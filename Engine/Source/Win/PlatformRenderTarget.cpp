
#include <PlatformRenderTarget.h>

WinRenderTarget::WinRenderTarget(HINSTANCE hInstance, HWND hWnd)
{
    this->hInstance = hInstance;
    this->hWnd = hWnd;

    // create additional hWnd
    auto dwStyle = WS_CHILD | WS_VISIBLE;
    auto size = getSize();
    this->hWndEx = CreateWindowEx(NULL, L"EDIT", L"", dwStyle, 0, 0, size.x, size.y, hWnd, NULL, hInstance, NULL);
}

void WinRenderTarget::onRendering(RendererType type)
{
    if (type == RendererType::DX)
    {
        auto size = getSize();
        SetWindowPos(hWndEx, 0, 0, 0, size.x, size.y, 0);
        ShowWindow(hWndEx, SW_SHOW);
    }
    else
    {
        ShowWindow(hWndEx, SW_HIDE);
    }
}

Vector2 WinRenderTarget::getSize() const
{
    RECT rect;
    GetClientRect(hWnd, &rect);
    return Vector2(rect.right - rect.left, rect.bottom - rect.top);
}
