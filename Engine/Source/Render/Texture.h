
#pragma once

#include "RenderResource.h"
#include <Path.h>
#include <string>

class Texture : public RenderResource<Texture>
{
public:
    Texture(Path filePath);
    void load();

public:
    Path filePath;
};
