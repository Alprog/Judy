
#pragma once

#include <vector>

class IndexBuffer
{
public:
    IndexBuffer();
    void Load();

    std::vector<uint32_t> indices;

    void* impl[2];
};
