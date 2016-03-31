
#pragma once

#include "Renderer.h"

#include <windows.h>
#include <d3d12.h>

class DXRenderer : public Renderer
{
public:
    DXRenderer();

    virtual void Draw(Mesh* mesh, Matrix matrix, RenderState* renderState) override;
    virtual void DrawQuad(Quad* quad) override;
    virtual void Render(Node* scene, RenderTarget* renderTarget) override;

    void Clear(Color color) override;

private:
    void InitQuad();

};

