
#pragma once

#include "Renderer.h"
#include "GLContext.h"

class GLRenderer : Renderer
{
public:
    std::unordered_map<RenderTarget*, GLContext*> contexts;

    GLContext* GetContext(RenderTarget* renderTarget);

    void Render(Scene* scene, RenderTarget* renderTarget) override;

    void Clear(Color color) override;
};

