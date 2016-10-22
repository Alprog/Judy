
#pragma once

#include "IRenderer.h"
#include "RendererResource.h"

template <RendererType RendererT>
class Renderer : public IRenderer
{
public:
    virtual RendererType getType() override { return RendererT; }

    virtual void createImpl(Texture* resource) override { helper(resource); }
    virtual void createImpl(Shader* resource) override { helper(resource); }
    virtual void createImpl(VertexBuffer* resource) override { helper(resource); }
    virtual void createImpl(ConstantBuffer* resource) override { helper(resource); }
    virtual void createImpl(IndexBuffer* resource) override { helper(resource); }

    template <typename ResourceT>
    inline Impl<ResourceT, RendererT>* getImpl(ResourceT* const resource)
    {
        return static_cast<Impl<ResourceT, RendererT>*>(resourceImpls[resource->id]);
    }

    template <typename ResourceT>
    inline Impl<ResourceT, RendererT>* getImpl(unsigned int id)
    {
        return static_cast<Impl<ResourceT, RendererT>*>(resourceImpls[id]);
    }

protected:
    std::vector<void*> resourceImpls;

    template <typename ResourceT>
    inline void helper(ResourceT* resource)
    {
        auto id = resource->id;

        if (id >= resourceImpls.size())
        {
            resourceImpls.resize(id + 1);
        }

        resourceImpls[id] = (void*)new Impl<ResourceT, RendererT>(Any(this), resource);
    }
};
