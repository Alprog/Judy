
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
        auto b = glGetError();
        glBindBuffer(GL_ARRAY_BUFFER, id);
        auto a = glGetError();
        if (a != 0)
        {
            throw b - a;
        }
    }

private:
    GLuint id;
};
