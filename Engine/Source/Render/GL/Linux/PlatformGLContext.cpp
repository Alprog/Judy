
#include "PlatformGLContext.h"
#include <PlatformRenderTarget.h>
#include <GL/glx.h>


using glXCreateContextAttribsARBProc = GLXContext (*)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

LinuxGLContext::LinuxGLContext(RenderTarget* renderTarget)
{
    auto rt = static_cast<LinuxRenderTarget*>(renderTarget);

    this->display = rt->display;
    this->window = rt->window;

    init();
}

LinuxGLContext::LinuxGLContext()
    : window{0}
{
    this->display = XOpenDisplay(0);
    init();
}

void LinuxGLContext::init()
{
    static int visual_attribs[] =
    {
       GLX_RENDER_TYPE, GLX_RGBA_BIT,
       GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
       GLX_DOUBLEBUFFER, true,
       GLX_RED_SIZE, 1,
       GLX_GREEN_SIZE, 1,
       GLX_BLUE_SIZE, 1,
       None
    };

    static int context_attribs[] =
    {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 4,
        None
    };

    int num_fbc = 0;
    GLXFBConfig* fbc = glXChooseFBConfig(display, DefaultScreen(display), visual_attribs, &num_fbc);
    auto glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");
    static GLXContext lastContext = NULL;
    lastContext = glXCreateContextAttribsARB(display, fbc[0], lastContext, true, context_attribs);
    glc = lastContext;

    if (glGetError() != GL_NO_ERROR)
    {
        exit(0);
    }
}

void LinuxGLContext::makeCurrent()
{
    if (!glXMakeCurrent(display, window, glc))
    {
        throw;
    }
}

void LinuxGLContext::swap()
{
    glXSwapBuffers(display, window);
}
