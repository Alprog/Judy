
#pragma once

#include <string>
#include "RendererResource.h"

class Shader : public RendererResource<Shader>
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
};
