
#pragma once

#include "RendererType.h"
#include <Impl.h>
#include <IRenderer.h>

class IRenderResource
{
public:
    IRenderResource();
    ~IRenderResource();

    virtual void initForRenderer(IRenderer* renderer) = 0;

    unsigned int id;
};

template <RendererType T>
class Renderer;

template <typename ResourceType>
class RenderResource : public IRenderResource
{
public:
    template <RendererType RendererT>
    inline Impl<ResourceType, RendererT>* getImpl(Renderer<RendererT>* renderer)
    {
        return renderer->getImpl((ResourceType*)this);
    }

    virtual void initForRenderer(IRenderer* renderer) override
    {
        auto resource = static_cast<ResourceType*>(this);
        renderer->createImpl(resource);
    }
};
