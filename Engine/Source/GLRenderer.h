
#pragma once

#include "Renderer.h"
#include "GLContext.h"

class GLRenderer : public Renderer
{
public:
    GLRenderer();

    std::unordered_map<RenderTarget*, GLContext*> contexts;

    GLContext* GetContext(RenderTarget* renderTarget);

    virtual void Draw(Mesh* mesh, Material* material, Matrix matrix) override;

    virtual void DrawQuad(Quad* quad) override;
    virtual void Render(Node* scene, RenderTarget* renderTarget) override;

    virtual void Clear(Color color) override;
};

