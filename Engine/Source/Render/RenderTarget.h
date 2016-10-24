
#pragma once

#include "Math/Vector2.h"
#include "RendererType.h"

class RenderTarget
{
public:
    virtual void onRendering(RendererType type) = 0;
    virtual Vector2 getSize() const = 0;
};
