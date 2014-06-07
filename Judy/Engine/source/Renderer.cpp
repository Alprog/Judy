
#include "Renderer.h"
#include <stdio.h>

#if WIN
    #include <windows.h>
#endif

#if MAC
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif


namespace Judy
{
    Renderer::Renderer(Window* window, bool a)
    {
        window->SetContext();

        glClearColor(0.0f, a ? 0.0f : 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window->Swap();
    }
}
