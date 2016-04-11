
#pragma once

#include "RendererResource.h"

class ConstantBuffer : public RendererResource<ConstantBuffer>
{
public:
    ConstantBuffer();

    void Load();
};
