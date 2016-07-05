
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

template <typename T>
class RendererResource : public RenderResource
{
public:
    RendererResource()
        : impl {}
    {
    }

    template <typename R, RendererType RT>
    inline Impl<T, RT>* GetImpl(RendererBase<R, RT>* renderer)
    {
        return static_cast<Impl<T, RT>*>(renderer->resourceImpls[id]);
    }

    union
    {
        void* impl[RendererType::Count];

        struct
        {
            Impl<T, RendererType::DX>* dxImpl;
            Impl<T, RendererType::GL>* glImpl;
        };
    };
};
