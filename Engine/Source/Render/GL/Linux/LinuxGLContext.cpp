
#include "LinuxGLContext.h"
#include <PlatformRenderTarget.h>

const GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, 0 };

LinuxGLContext::LinuxGLContext(RenderTarget* renderTarget)
{
    auto rt = static_cast<LinuxRenderTarget*>(renderTarget);

    this->display = rt->display;
    this->window = rt->window;

    XVisualInfo* vi = glXChooseVisual(rt->display, 0, att);
    glc = glXCreateContext(rt->display, vi, NULL, GL_TRUE);
}

LinuxGLContext::LinuxGLContext()
    : window{0}
{
    display = XOpenDisplay(0);
    XVisualInfo* vi = glXChooseVisual(display, 0, att);
    glc = glXCreateContext(display, vi, NULL, GL_TRUE);
}

void LinuxGLContext::makeCurrent()
{
    glXMakeCurrent(display, window, glc);
}

void LinuxGLContext::swap()
{
    glXSwapBuffers(display, window);
}
