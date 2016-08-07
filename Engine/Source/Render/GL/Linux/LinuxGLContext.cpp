
#include "LinuxGLContext.h"
#include "LinuxRenderTarget.h"

const GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

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

void LinuxGLContext::MakeCurrent()
{
    glXMakeCurrent(display, window, glc);
}

void LinuxGLContext::Swap()
{
    static float a = 0;
    a = 1 - a;

    glClearColor( 1.0, a, 0.0, 1.0 );
    glClear(GL_COLOR_BUFFER_BIT);
    glXSwapBuffers(display, window);
}
