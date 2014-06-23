
#pragma once

#include "Window.h"

class Renderer
{
public:
    virtual void Render(Scene* scene, SwapChain* context) = 0;
};
