
#pragma once

#include <string>

class Texture
{
public:
    Texture(std::string name);
    void Load();

public:
    std::string name;
    void* impl[2];
};
