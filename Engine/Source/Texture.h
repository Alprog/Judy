
#pragma once

#include <string>

class Texture
{
public:
    Texture(std::string name);
    void Load();

protected:
    std::string name;
    void* impl[2];
};
