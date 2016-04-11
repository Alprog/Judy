
#pragma once

#include "gl.h"

#include "../Impl.h"

class GLRenderer;
class VertexBuffer;

class GLVertexBufferImpl
{
public:
    GLVertexBufferImpl(GLRenderer* renderer, VertexBuffer* vertexBuffer);

    inline void Bind() { glBindBuffer(GL_ARRAY_BUFFER, id); }

    GLuint id;
};
