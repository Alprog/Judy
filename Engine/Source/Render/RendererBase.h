
#pragma once

#include "Renderer.h"

template <typename T>
class RendererBase : public Renderer
{
public:
    virtual void* CreateImpl(Texture* resource) override { return Helper(resource); }
    virtual void* CreateImpl(Shader* resource) override { return Helper(resource); }
    virtual void* CreateImpl(VertexBuffer* resource) override { return Helper(resource); }
    virtual void* CreateImpl(ConstantBuffer* resource) override { return Helper(resource); }
    virtual void* CreateImpl(IndexBuffer* resource) override { return Helper(resource); }

private:
    template <typename Resource>
    inline void* Helper(Resource* resource)
    {
        return new Impl<Resource, T::rendererType>(static_cast<T*>(this), resource);
    }
};
