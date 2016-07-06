
#pragma once

#include "IRenderer.h"
#include "RendererResource.h"

template <RendererType RendererT>
class Renderer : public IRenderer
{
public:
    virtual void CreateImpl(Texture* resource) override { Helper(resource); }
    virtual void CreateImpl(Shader* resource) override { Helper(resource); }
    virtual void CreateImpl(VertexBuffer* resource) override { Helper(resource); }
    virtual void CreateImpl(ConstantBuffer* resource) override { Helper(resource); }
    virtual void CreateImpl(IndexBuffer* resource) override { Helper(resource); }

    template <typename ResourceT>
    inline Impl<ResourceT, RendererT>* GetImpl(ResourceT* const resource)
    {
        return static_cast<Impl<ResourceT, RendererT>*>(resourceImpls[resource->id]);
    }

    template <typename ResourceT>
    inline Impl<ResourceT, RendererT>* GetImpl(unsigned int id)
    {
        return static_cast<Impl<ResourceT, RendererT>*>(resourceImpls[id]);
    }

protected:
    std::vector<void*> resourceImpls;

    template <typename ResourceT>
    inline void Helper(ResourceT* resource)
    {
        auto id = resource->id;

        if (id >= resourceImpls.size())
        {
            resourceImpls.resize(id + 1);
        }

        resourceImpls[id] = (void*)new Impl<ResourceT, RendererT>(Any(this), resource);
    }
};
