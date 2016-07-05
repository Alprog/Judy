
#pragma once

#include "Renderer.h"
#include "RendererResource.h"

template <typename T, RendererType RT>
class RendererBase : public Renderer
{
public:
    virtual void CreateImpl(Texture* resource) override { Helper(resource); }
    virtual void CreateImpl(Shader* resource) override { Helper(resource); }
    virtual void CreateImpl(VertexBuffer* resource) override { Helper(resource); }
    virtual void CreateImpl(ConstantBuffer* resource) override { Helper(resource); }
    virtual void CreateImpl(IndexBuffer* resource) override { Helper(resource); }

    template <typename Resource>
    inline Impl<Resource, RT>* GetImpl(Resource* resource)
    {
        return static_cast<Impl<Resource, RT>*>(resourceImpls[resource->id]);
    }

    template <typename Resource>
    inline Impl<Resource, RT>* GetImpl(unsigned int id)
    {
        return static_cast<Impl<Resource, RT>*>(resourceImpls[id]);
    }

    std::vector<void*> resourceImpls;
protected:

    template <typename Resource>
    inline void Helper(Resource* resource)
    {
        auto id = ((RenderResource*)resource)->id;

        if (id >= resourceImpls.size())
        {
            resourceImpls.resize(id + 1);
        }

        resourceImpls[id] = (void*)new Impl<Resource, RT>(static_cast<T*>(this), resource);
    }
};
