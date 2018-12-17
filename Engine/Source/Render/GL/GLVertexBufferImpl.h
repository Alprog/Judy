
#pragma once

#include <Impl.h>
#include <VertexBuffer.h>
#include <gl.h>

class GLRenderer;

template <>
class Impl<VertexBuffer, RendererType::GL>
{
public:
    Impl(GLRenderer* renderer, VertexBuffer* vertexBuffer);

    inline void bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

private:
    GLuint id;
};
