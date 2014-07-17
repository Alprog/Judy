
#include "GLRenderer.h"

#include "Scene.h"

#if WIN
    #include <windows.h>
#endif

#if MAC
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#include "Win/WinGLContext.h"
#include "Win/WinRenderTarget.h"

void GLRenderer::Clear(Color color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLContext* GLRenderer::GetContext(RenderTarget* renderTarget)
{
    auto context = (GLContext*)contexts[renderTarget];
    if (context == nullptr)
    {
        auto hWnd = ((WinRenderTarget*)renderTarget)->hWnd;
        context = (GLContext*)new WinGLContext(hWnd);
        contexts[renderTarget] = context;
    }
    return context;
}

void GLRenderer::Render(Scene *scene, RenderTarget* renderTarget)
{
    auto context = GetContext(renderTarget);

    context->MakeCurrent();

    glViewport(-400, 0, 800, 800);
    glScissor(0, 0, 400, 800);
    glEnable(GL_SCISSOR_TEST);

    Color color { 0.0f, 1.0f, 0.0f, 1.0f };
    Clear(color);

    glBegin(GL_TRIANGLES);

    glVertex3f(-0.8f, 0.8f, 0.0f);
    glVertex3f(0.8f, 0.8f, 0.0f);
    glVertex3f(-0.8f, -0.8f, 0.0f);
    glVertex3f(-0.8f, -0.8f, 0.0f);
    glVertex3f(0.8f, 0.8f, 0.0f);
    glVertex3f(0.8f, -0.8f, 0.0f);

    glEnd();

    context->Swap();
}
