
#include "Renderer.h"
#include <stdio.h>

#if WIN
    #include <windows.h>
    #include "Gl/Gl.h"
#else
    #include <OpenGL/gl.h>
#endif

namespace  Judy {


Renderer::Renderer(JWindow* window, bool a)
{
    window->SetContext();

    glClearColor(0.0f, a ? 0.0f : 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    window->Swap();
}


}
