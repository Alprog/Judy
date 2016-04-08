
#pragma once

#include <vector>

class IndexBuffer
{
public:
    void Load();

    std::vector<uint32_t> indices;

    void* impl[2];
};
