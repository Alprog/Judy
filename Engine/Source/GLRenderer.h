
#pragma once

#include "Renderer.h"
#include "GLContext.h"

class Shader;
class Texture;

class GLRenderer : public Renderer
{
public:
    GLRenderer();

    std::unordered_map<RenderTarget*, GLContext*> contexts;

    GLContext* GetContext(RenderTarget* renderTarget);

    virtual void Draw(Mesh* mesh, Matrix matrix, RenderState* renderState) override;

    virtual void DrawQuad(Quad* quad) override;
    virtual void Render(Node* scene, RenderTarget* renderTarget) override;

    virtual void Clear(Color color) override;

    virtual void* CreateTexture(Texture* texture) override;
    virtual void* CreateShader(Shader* shader) override;
};

