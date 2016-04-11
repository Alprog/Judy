
#pragma once

#include "RendererResource.h"

class ConstantBuffer : public RendererResource<ConstantBuffer>
{
    ConstantBuffer();

    void Load();
};
