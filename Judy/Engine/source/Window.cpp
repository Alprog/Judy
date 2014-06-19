
#include "Window.h"
#include "Platforms.h"

#if WIN
    #include <windows.h>
#endif

#if MAC
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

Window* Window::Create()
{
    return (Window*)new PlatformWindow();
}

void Window::Render()
{
    context->MakeCurrent();

    static bool a = true; a = !a;
    glClearColor(0.0f, a ? 0.0f : 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    context->Swap();
}

void Window::show()
{
}

