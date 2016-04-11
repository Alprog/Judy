
#pragma once

#include "../Renderer.h"
#include "../RendererBase.h"

#include "GLContext.h"

#include "../RendererType.h"
#include "GLShaderImpl.h"
#include "GLTextureImpl.h"
#include "GLIndexBufferImpl.h"
#include "GLVertexBufferImpl.h"
#include "GLConstantBufferImpl.h"

class Shader;
class Texture;

class GLRenderer : public RendererBase<GLRenderer>
{
public:
    static const RendererType rendererType = RendererType::GL;

    GLRenderer();

    std::unordered_map<RenderTarget*, GLContext*> contexts;

    GLContext* GetContext(RenderTarget* renderTarget);

    virtual void Draw(Mesh* mesh, Matrix matrix, RenderState* renderState) override;

    virtual void DrawQuad(Quad* quad) override;
    virtual void Render(Node* scene, RenderTarget* renderTarget) override;

    virtual void Clear(Color color) override;
};

