
#pragma once

#include "Renderer.h"

class GLRenderer : Renderer
{
public:
    void Render(Scene* scene, Context* context) override;
};

