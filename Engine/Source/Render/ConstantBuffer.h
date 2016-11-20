
#pragma once

#include "Math/Matrix.h"
#include "RenderResource.h"

class ConstantBuffer : public RenderResource<ConstantBuffer>
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
