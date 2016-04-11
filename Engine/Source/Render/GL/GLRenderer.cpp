
#include "GLRenderer.h"

#include "Node.h"

#if WIN
    #include <windows.h>
#endif

#include "gl.h"

#include "Win/WinGLContext.h"
#include "Win/WinRenderTarget.h"

#include "GLShaderImpl.h"
#include "GLTextureImpl.h"
#include "GLIndexBufferImpl.h"
#include "GLVertexBufferImpl.h"
#include "../Texture.h"

#include "../IndexBuffer.h"
#include "../VertexBuffer.h"

GLRenderer::GLRenderer()
{
    auto dummy = (GLContext*)new WinGLContext(0);
    dummy->MakeCurrent();
    glewInit();
    //delete dummy;
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

void GLRenderer::Draw(Mesh* mesh, Matrix matrix, RenderState* renderState)
{
    glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);

    glDisable(GL_CULL_FACE);

    auto mvp = matrix * Matrix::RotationX(3.1416) * Matrix::OrthographicLH(2, 2, -2, 2);

    /*for (auto i = 0; i < mesh->vertices.size(); i++)
    {
        auto v3 = mesh->vertices[i].Position;
        auto v4 = v3 * mvp;

        printf("%i\n", v4.x);
    }*/

    GLuint location = glGetUniformLocation(renderState->programId, "MVP");
    glUniformMatrix4fv(location, 1, GL_FALSE, &mvp.m11);

    location = glGetUniformLocation(renderState->programId, "mainTexture");
    glUniform1i(location, 0);

    glActiveTexture(GL_TEXTURE0);
    GLuint id = static_cast<GLTextureImpl*>(renderState->texture->impl[1])->id;
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    auto vb = static_cast<GLVertexBufferImpl*>(mesh->vertexBuffer->impl[1]);


    mesh->indexBuffer->glImpl->Bind();

    vb->Bind();

    glUseProgram(renderState->programId);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);

    glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);

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

void* GLRenderer::CreateTexture(Texture* texture)
{
    return new GLTextureImpl(this, texture);
}

void* GLRenderer::CreateShader(Shader* shader)
{
    return new GLShaderImpl(this, shader);
}

void* GLRenderer::CreateVertexBuffer(VertexBuffer* vertexBuffer)
{
    return new GLVertexBufferImpl(this, vertexBuffer);
}

void* GLRenderer::CreateIndexBuffer(IndexBuffer* indexBuffer)
{
    return new Impl<IndexBuffer, RendererType::GL>(this, indexBuffer);
}
