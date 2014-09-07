
#pragma once

#include "Renderer.h"
#include "GLContext.h"

class GLRenderer : Renderer
{
public:
    std::unordered_map<RenderTarget*, GLContext*> contexts;

    GLContext* GetContext(RenderTarget* renderTarget);

    void DrawQuad(Quad* quad) override;
    void Render(Node* scene, RenderTarget* renderTarget) override;

    void Clear(Color color) override;
};

