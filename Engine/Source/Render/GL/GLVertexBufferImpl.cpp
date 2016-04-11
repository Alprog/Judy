
#include "GLVertexBufferImpl.h"

#include "../VertexBuffer.h"

GLVertexBufferImpl::GLVertexBufferImpl(GLRenderer* renderer, VertexBuffer* vertexBuffer)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, vertexBuffer->vertices.size() * sizeof(Vertex), &vertexBuffer->vertices[0], GL_STATIC_DRAW);

    printf("id: %i %i\n", id, vertexBuffer->vertices.size());
}
