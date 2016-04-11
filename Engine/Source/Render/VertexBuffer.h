
#pragma once

#include <vector>
#include "Vertex.h"

#include "RendererResource.h"

class VertexBuffer : public RendererResource<VertexBuffer>
{
public:
    VertexBuffer();

    void Load();

    std::vector<Vertex> vertices;
};
