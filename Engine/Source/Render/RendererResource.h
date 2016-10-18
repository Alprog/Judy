
#pragma once

#include "RendererType.h"
#include "Impl.h"

class RenderResource
{
public:
    RenderResource();
    ~RenderResource();

    unsigned int id;
};

template <RendererType T>
class Renderer;

template <typename ResourceType>
class RendererResource : public RenderResource
{
public:
    template <RendererType RendererT>
    inline Impl<ResourceType, RendererT>* getImpl(Renderer<RendererT>* renderer)
    {
        return renderer->getImpl((ResourceType*)this);
    }
};
