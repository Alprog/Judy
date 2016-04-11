
#pragma once

#include "../Renderer.h"
#include "GLContext.h"

#include "../RendererType.h"
#include "GLShaderImpl.h"
#include "GLTextureImpl.h"
#include "GLIndexBufferImpl.h"
#include "GLVertexBufferImpl.h"
#include "GLConstantBufferImpl.h"

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

    virtual void* CreateImpl(Texture* resource) override { return new Impl<Texture, RendererType::GL>(this, resource); }
    virtual void* CreateImpl(Shader* resource) override { return new Impl<Shader, RendererType::GL>(this, resource); }
    virtual void* CreateImpl(VertexBuffer* resource) override { return new Impl<VertexBuffer, RendererType::GL>(this, resource); }
    virtual void* CreateImpl(IndexBuffer* resource) override { return new Impl<IndexBuffer, RendererType::GL>(this, resource); }
    virtual void* CreateImpl(ConstantBuffer* resource) override { return new Impl<ConstantBuffer, RendererType::GL>(this, resource); }
};

