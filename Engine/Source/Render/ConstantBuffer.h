
#pragma once

#include "Math/Matrix.h"
#include "RendererResource.h"

class ConstantBuffer : public RendererResource<ConstantBuffer>
{
public:
    ConstantBuffer();

    void load();

    struct
    {
        Matrix MVP;
    }
    data;
};
