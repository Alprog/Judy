
#include "GLRenderer.h"

#include "Scene.h"
#include "Context.h"

#if WIN
    #include <windows.h>
#endif

#if MAC
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

void GLRenderer::Render(Scene *scene, Context *context)
{
    context->MakeCurrent();

    glViewport(0, 0, 800, 800);
    glScissor(0, 0, 400, 800);
    glEnable(GL_SCISSOR_TEST);

    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.2, 0.3);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(0, 1, 0);
    glEnd();

    context->Swap();
}
