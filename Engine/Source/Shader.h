
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

    virtual void Compile() = 0;


protected:
    std::string source;
    Type type;
};
