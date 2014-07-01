
#pragma once

#include "Window.h"
#include "Color.h"

class Renderer
{
public:
    virtual void Render(Scene* scene, SwapChain* context) = 0;

    virtual void Clear(Color color) = 0;
};
