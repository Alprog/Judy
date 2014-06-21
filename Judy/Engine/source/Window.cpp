
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

#include <d3d.h>

Window* Window::Create()
{
    return (Window*)new PlatformWindow();
}

void Window::Render()
{
    context->MakeCurrent();

    glViewport(0, 0, 400, 400);

    static bool a = true; a = !a;
    glClearColor(0.0f, a ? 0.0f : 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.2, 0.3);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(0, 1, 0);
    glEnd();

    context->Swap();
}

void Window::show()
{
}

