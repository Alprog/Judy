
#pragma once

#include "RendererResource.h"
#include <string>

class Texture : public RendererResource<Texture>
{
public:
    Texture(std::string name);
    void Load();

public:
    std::string name;
};
