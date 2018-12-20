
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

#include "App.h"

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

    // terrible hack for linux:
    auto app = App::getInstance();
    app->updateCollection();
    Window* w = *app->windows.begin();
    getContext(w->renderTarget)->makeCurrent();

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

    return context;
}

void CheckGL()
{
    auto a = glGetError();
    if (a != 0)
    {
        throw 0;
    }
}

void GLRenderer::draw(RenderCommand command)
{
    CheckGL();

    glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
    CheckGL();

    glDisable(GL_CULL_FACE);
    CheckGL();


    auto renderState = command.state;

    auto programId = getImpl(renderState->getPipelineState())->programId;

    GLuint id = getImpl(renderState->texture)->id;
    glBindTexture(GL_TEXTURE_2D, id);
    CheckGL();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    CheckGL();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    CheckGL();

    getImpl(command.state->constantBuffer)->update();
    getImpl(command.mesh->vertexBuffer)->bind();

    static GLuint vao = 0;
    if (vao == 0)
    {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
    }

    CheckGL();
    getImpl(command.state->constantBuffer)->bind();
    CheckGL();
    getImpl(command.mesh->indexBuffer)->bind();
    CheckGL();
    glUseProgram(programId);
    CheckGL();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    CheckGL();
    glDrawElements(GL_TRIANGLES, command.mesh->indices.size(), GL_UNSIGNED_INT, 0);
    CheckGL();
    fflush(stdout);
    CheckGL();

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
