
#pragma once

#include "Renderer.h"

class GLRenderer : Renderer
{
public:
    void Render(Scene* scene, SwapChain* context) override;
};

