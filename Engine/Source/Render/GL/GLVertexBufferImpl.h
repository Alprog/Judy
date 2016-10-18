
#pragma once

#include "gl.h"

#include "../Impl.h"
#include "../VertexBuffer.h"

class GLRenderer;

template <>
class Impl<VertexBuffer, RendererType::GL>
{
public:
    Impl(GLRenderer* renderer, VertexBuffer* vertexBuffer);

    inline void bind() { glBindBuffer(GL_ARRAY_BUFFER, id); }

    GLuint id;
};
