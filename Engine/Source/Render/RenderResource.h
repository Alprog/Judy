
#pragma once

#include "RendererType.h"
#include "Impl.h"

class IRenderResource
{
public:
    IRenderResource();
    ~IRenderResource();

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
};
