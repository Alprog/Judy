
#pragma once

#include <vector>
#include "RendererResource.h"

class IndexBuffer : public RendererResource<IndexBuffer>
{
public:
    IndexBuffer();
    void Load();

    std::vector<uint32_t> indices;
};
