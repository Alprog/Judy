
#pragma once

#include "RendererType.h"
#include "Impl.h"

template <typename T>
class RendererResource
{
public:
    RendererResource()
        : impl {}
    {
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
