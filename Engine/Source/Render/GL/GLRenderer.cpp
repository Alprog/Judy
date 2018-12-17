
#include "GLRenderer.h"

#include "Node.h"

#if WIN
    #include <windows.h>
    #include <PlatformRenderTarget.h>
    #include <PlatformWindow.h>
#endif

#include <PlatformGLContext.h>

#include "gl.h"
#include "../Texture.h"

#include "../IndexBuffer.h"
#include "../VertexBuffer.h"
#include "../ConstantBuffer.h"

GLRenderer::GLRenderer()
{
    printf("gl initing\n");

    auto dummy = new PlatformGLContext();
    dummy->makeCurrent();
    auto result = glewInit();

    if (result != GLEW_OK)
    {
        printf("glew init error %i\n", result);
    }
    delete dummy;

    printf("gl inited\n");
}

void GLRenderer::clear(Color color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLContext* GLRenderer::getContext(RenderTarget* renderTarget)
{
    auto context = (GLContext*)contexts[renderTarget];
    if (context == nullptr)
    {
        context = new PlatformGLContext(renderTarget);
        contexts[renderTarget] = context;
    }

    //context->makeCurrent();

    return context;
}

void GLRenderer::draw(RenderCommand command)
{
    GLenum a = glGetError();

    glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
    a = glGetError();

    glDisable(GL_CULL_FACE);
    a = glGetError();

    auto renderState = command.state;

    auto programId = getImpl(renderState->getPipelineState())->programId;

    auto location = glGetUniformLocation(programId, "mainTexture");
    glUniform1i(location, 0);
    glActiveTexture(GL_TEXTURE0);
    a = glGetError();

    GLuint id = getImpl(renderState->texture)->id;
    glBindTexture(GL_TEXTURE_2D, id);
    a = glGetError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    a = glGetError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    a = glGetError();

    getImpl(command.state->constantBuffer)->update();

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    command.mesh->vertexBuffer->Load();

    getImpl(command.state->constantBuffer)->bind();
    getImpl(command.mesh->vertexBuffer)->bind();
    getImpl(command.mesh->indexBuffer)->bind();
    glUseProgram(programId);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnableVertexAttribArray(0);
    a = glGetError();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    a = glGetError();
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);

    a = glGetError();
    glDrawElements(GL_TRIANGLES, command.mesh->indices.size(), GL_UNSIGNED_INT, 0);
    a = glGetError();

    fflush(stdout);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void GLRenderer::render(std::vector<RenderCommand> commands, RenderTarget* renderTarget)
{
    auto context = getContext(renderTarget);

    context->makeCurrent();

    auto size = renderTarget->getSize();
    glViewport(0, 0, size.x, size.y);

    //glScissor(0, 0, 400, 800);
    //glEnable(GL_SCISSOR_TEST);

    // CODE

    Color color
    {
        (float)'J' / 255,
        (float)'u' / 255,
        (float)'d' / 255,
        (float)'y' / 255
    };

    clear(color);

    for (auto& command : commands)
    {
        draw(command);
    }

    context->swap();
}
