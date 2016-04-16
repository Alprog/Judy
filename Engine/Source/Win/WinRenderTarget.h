
#pragma once

#include "Render/RenderTarget.h"
#include <windows.h>

class WinRenderTarget : public RenderTarget
{
public:
    WinRenderTarget(HWND hWnd);
    virtual Vector2 GetSize() const override;

    HWND hWnd;
};
