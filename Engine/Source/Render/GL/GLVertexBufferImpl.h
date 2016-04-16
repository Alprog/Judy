
#pragma once

#include "gl.h"

#include "../Impl.h"

class GLRenderer;
class VertexBuffer;

template <>
class Impl<VertexBuffer, RendererType::GL>
{
public:
    Impl(GLRenderer* renderer, VertexBuffer* vertexBuffer);

    inline void Bind() { glBindBuffer(GL_ARRAY_BUFFER, id); }

    GLuint id;
};
