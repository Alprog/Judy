
#pragma once

#include <Impl.h>
#include <ConstantBuffer.h>
#include <gl.h>

class GLRenderer;

template <>
class Impl<ConstantBuffer, RendererType::GL>
{
public:
    Impl(GLRenderer* renderer, ConstantBuffer* constantBuffer);

    inline void bind() { glBindBufferBase(GL_UNIFORM_BUFFER, 0, id); }
    void update();

private:
    ConstantBuffer* resource;
    int version;
    GLuint id;
};
