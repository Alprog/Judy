
#include "GLRenderer.h"

#include "Node.h"

#if WIN
    #include <windows.h>
#endif

#if MAC
    #include <OpenGL/gl.h>
#else
    #define GLEW_STATIC
    #include <GL/glew.h>
    #include <GL/gl.h>
#endif

#include "Win/WinGLContext.h"
#include "Win/WinRenderTarget.h"

GLRenderer::GLRenderer()
{
}

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

    context->MakeCurrent();
    glewInit();

    return context;
}

GLuint vertexbuffer = 0;

void GLRenderer::Draw(Mesh* mesh, Matrix matrix, RenderState* renderState)
{
    glLoadMatrixf((float*)&matrix);

    glDisable(GL_CULL_FACE);

    if (vertexbuffer == 0)
    {
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vertex), &mesh->vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    }

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, &mesh->indices[0]);

    glDisableVertexAttribArray(0);
}

void GLRenderer::DrawQuad(Quad* quad)
{
    glBegin(GL_TRIANGLES);

    auto x = quad->Size.x;
    auto y = quad->Size.y;

    glVertex3f(-x, y, 0.0f);
    glVertex3f(x, y, 0.0f);
    glVertex3f(-x, -y, 0.0f);
    glVertex3f(-x, -y, 0.0f);
    glVertex3f(x, y, 0.0f);
    glVertex3f(x, -y, 0.0f);

    glEnd();
}

void GLRenderer::Render(Node* scene, RenderTarget* renderTarget)
{
    auto context = GetContext(renderTarget);

    context->MakeCurrent();

    auto size = renderTarget->GetSize();
    glViewport(0, 0, size.x, size.y);

    //glScissor(0, 0, 400, 800);
    //glEnable(GL_SCISSOR_TEST);

    Color color { 0.3f, 0.3f, 0.3f, 1.0f };
    Clear(color);

    scene->Render(scene->transform.getMatrix(), this);

    context->Swap();
}
