
#include "GLVertexBufferImpl.h"

void glCheck()
{
    auto a = glGetError();
    if (a != 0)
    {
        throw 0;
    }
}

Impl<VertexBuffer, RendererType::GL>::Impl(GLRenderer* renderer, VertexBuffer* vertexBuffer)
{
    glCheck();
    glGenBuffers(1, &id);
    glCheck();
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glCheck();
    glBufferData(GL_ARRAY_BUFFER, vertexBuffer->vertices.size() * sizeof(Vertex), &vertexBuffer->vertices[0], GL_STATIC_DRAW);
    glCheck();

    printf("id: %i %i %i\n", id, vertexBuffer->vertices.size(), glGetError());
}
