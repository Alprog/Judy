
#pragma once

#include <vector>
#include "Vertex.h"
#include <stdint.h>

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

Mesh* CreateCubeMesh();
