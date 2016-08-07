
#pragma once

#include "../GLContext.h"

#define Window XWindow
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#undef Window

#include "Render/RenderTarget.h"

class LinuxGLContext : public GLContext
{
public:
    LinuxGLContext();
    LinuxGLContext(RenderTarget* renderTarget);

    virtual void MakeCurrent() override;
    virtual void Swap() override;

    Display* display;
    XWindow window;
    GLXContext glc;
};
