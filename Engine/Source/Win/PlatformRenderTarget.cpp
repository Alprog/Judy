
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
    ShowWindow(hWndEx, type == RendererType::DX ? SW_SHOW : SW_HIDE);
}

Vector2 WinRenderTarget::getSize() const
{
    RECT rect;
    GetClientRect(hWnd, &rect);
    return Vector2(rect.right - rect.left, rect.bottom - rect.top);
}
