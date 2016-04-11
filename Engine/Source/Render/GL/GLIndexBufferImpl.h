
#pragma once

#include "gl.h"

#include "../Impl.h"

class IndexBuffer;
class GLRenderer;

template <>
class Impl<IndexBuffer, RendererType::GL>
{
public:
    Impl(GLRenderer* renderer, IndexBuffer* indexBuffer);

    inline void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }

    GLuint id;
};
