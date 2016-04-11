
#pragma once

#include <string>

class Shader
{
public:

    enum class Type
    {
        Vertex,
        Pixel
    };

    Shader(std::string source, Type type);
    void Load();

public:
    std::string source;
    Type type;

    void* impl[2];
};
