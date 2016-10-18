
#pragma once

#include "Render/RenderTarget.h"

#define Window XWindow
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#undef Window

class LinuxRenderTarget : public RenderTarget
{
public:
    LinuxRenderTarget(Display* display, XWindow window);

    virtual Vector2 getSize() const override;

    Display* display;
    XWindow window;
};

using PlatformRenderTarget = LinuxRenderTarget;
