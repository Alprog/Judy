
#pragma once

#include <vector>
#include "Vertex.h"

#include "RenderResource.h"

class VertexBuffer : public RenderResource<VertexBuffer>
{
public:
    VertexBuffer();

    void Load();

    std::vector<Vertex> vertices;
};
