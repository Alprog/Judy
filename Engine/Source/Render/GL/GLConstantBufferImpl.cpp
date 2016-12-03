
#include "GLConstantBufferImpl.h"

Impl<ConstantBuffer, RendererType::GL>::Impl(GLRenderer* renderer, ConstantBuffer* cb)
    : resource{cb}
    , version{cb->version}
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_UNIFORM_BUFFER, id);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(cb->data), &cb->data, GL_DYNAMIC_DRAW);
}

void Impl<ConstantBuffer, RendererType::GL>::update()
{
    if (version != resource->version)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, id);
        void* data = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
        memcpy(data, &resource->data, sizeof(resource->data));
        glUnmapBuffer(GL_UNIFORM_BUFFER);
    }
}

