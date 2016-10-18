
#pragma once

#include "RendererResource.h"
#include <string>

class Texture : public RendererResource<Texture>
{
public:
    Texture(std::string name);
    void load();

public:
    std::string name;
};
