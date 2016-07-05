
#pragma once

#include "RendererType.h"
#include "Impl.h"

template <typename T, RendererType RT>
class RendererBase;

class RenderResource
{
public:
    RenderResource();
    ~RenderResource();

    unsigned int id;
};

template <typename ResourceType>
class RendererResource : public RenderResource
{
public:
    template <typename R, RendererType RT>
    inline Impl<ResourceType, RT>* GetImpl(RendererBase<R, RT>* renderer)
    {
        return static_cast<Impl<ResourceType, RT>*>(renderer->resourceImpls[id]);
    }
};
