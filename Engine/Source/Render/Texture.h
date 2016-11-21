
#pragma once

#include "RenderResource.h"
#include <string>

class Texture : public RenderResource<Texture>
{
public:
    Texture(std::string name);
    void load();

public:
    std::string name;
};
