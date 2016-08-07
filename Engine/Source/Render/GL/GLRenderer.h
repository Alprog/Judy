
#pragma once

#include "../IRenderer.h"

#include "GLContext.h"

#include "../RendererType.h"
#include "GLShaderImpl.h"
#include "GLTextureImpl.h"
#include "GLIndexBufferImpl.h"
#include "GLVertexBufferImpl.h"
#include "GLConstantBufferImpl.h"
#include "../Renderer.h"

class Shader;
class Texture;

class GLRenderer : public Renderer<RendererType::GL>
{
public:
    GLRenderer();

    virtual void Render(std::vector<RenderCommand> commands, RenderTarget* target) override;
    virtual void Draw(RenderCommand renderCommand) override;

    std::unordered_map<RenderTarget*, GLContext*> contexts;

    GLContext* GetContext(RenderTarget* renderTarget);
    virtual void Clear(Color color) override;
};

