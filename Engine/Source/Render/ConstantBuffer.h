
#pragma once

#include "Math/Matrix.h"
#include "RendererResource.h"

class ConstantBuffer : public RendererResource<ConstantBuffer>
{
public:
    ConstantBuffer();

    void Load();

    struct
    {
        Matrix MVP;
    }
    data;
};
