
#pragma once

#include <vector>
#include "RenderResource.h"

class IndexBuffer : public RenderResource<IndexBuffer>
{
public:
    IndexBuffer();
    void Load();

    std::vector<unsigned int> indices;
};
