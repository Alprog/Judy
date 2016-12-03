
#pragma once

#include "Math/Matrix.h"
#include "RenderResource.h"

class ConstantBuffer : public RenderResource<ConstantBuffer>
{
public:
    ConstantBuffer();

    void load();
    void update();

    struct
    {
        Matrix MVP;
    }
    data;

    int version;
};
