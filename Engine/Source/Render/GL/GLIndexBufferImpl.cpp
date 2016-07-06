
#include "GLIndexBufferImpl.h"

Impl<IndexBuffer, RendererType::GL>::Impl(GLRenderer* renderer, IndexBuffer* indexBuffer)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->indices.size() * sizeof(uint32_t), &indexBuffer->indices[0], GL_STATIC_DRAW);
}
