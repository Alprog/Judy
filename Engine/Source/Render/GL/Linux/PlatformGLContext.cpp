
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
       GLX_RED_SIZE, 8,
       GLX_GREEN_SIZE, 8,
       GLX_BLUE_SIZE, 8,
       GLX_ALPHA_SIZE, 8,
       GLX_DEPTH_SIZE, 24,
       GLX_STENCIL_SIZE, 8,
       GLX_X_RENDERABLE, true,
       GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
       None
    };

    static int context_attribs[] =
    {
        //GLX_RENDER_TYPE, GLX_RGBA_TYPE,
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 4,
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
        None
    };

    int num_fbc = 0;
    GLXFBConfig* fbc = glXChooseFBConfig(display, DefaultScreen(display), visual_attribs, &num_fbc);
    int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

    int i;
    for (i=0; i < num_fbc; ++i)
    {
        XVisualInfo *vi = glXGetVisualFromFBConfig( display, fbc[i] );
        if ( vi )
        {
            int samp_buf, samples;
            glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
            glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLES       , &samples  );

            int a, b, c, d, e, f;
            glXGetFBConfigAttrib( display, fbc[i], GLX_DOUBLEBUFFER, &a);
            glXGetFBConfigAttrib( display, fbc[i], GLX_RED_SIZE, &b);
            glXGetFBConfigAttrib( display, fbc[i], GLX_GREEN_SIZE, &c);
            glXGetFBConfigAttrib( display, fbc[i], GLX_BLUE_SIZE, &d);
            glXGetFBConfigAttrib( display, fbc[i], GLX_DEPTH_SIZE, &e);
            glXGetFBConfigAttrib( display, fbc[i], GLX_STENCIL_SIZE, &f);

            printf("%i depth: %i, screen: %i rgb: %i %i %i (%i %i) %i %i %i %i %i, %i\n",
                   i, vi->depth, vi->screen, vi->red_mask, vi->green_mask, vi->blue_mask, samp_buf, samples, a, b, c, d, e, f);
            fflush(stdout);

            //printf( "  Matching fbconfig %d, visual ID 0x%2x: SAMPLE_BUFFERS = %d,"
            //      " SAMPLES = %d\n",
            //      i, vi -> visualid, samp_buf, samples );

            if ( best_fbc < 0 || samp_buf && samples > best_num_samp )
                best_fbc = i, best_num_samp = samples;
            if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
                worst_fbc = i, worst_num_samp = samples;
        }
        XFree( vi );
    }
    GLXFBConfig bestFbc = fbc[ best_fbc ];

    printf("MATCH %i\n", best_fbc);

    auto glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");
    static GLXContext lastContext = NULL;
    lastContext = glXCreateContextAttribsARB(display, bestFbc, lastContext, true, context_attribs);
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
