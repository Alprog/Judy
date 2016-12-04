
#pragma once

#include "GLContext.h"

#include <Renderer.h>
#include "../RendererType.h"
#include "GLShaderImpl.h"
#include "GLTextureImpl.h"
#include "GLIndexBufferImpl.h"
#include "GLVertexBufferImpl.h"
#include "GLConstantBufferImpl.h"
#include "GLPipelineStateImpl.h"

class Shader;
class Texture;

class GLRenderer : public Renderer<RendererType::GL>
{
public:
    GLRenderer();

    virtual void render(std::vector<RenderCommand> commands, RenderTarget* target) override;
    virtual void draw(RenderCommand renderCommand) override;

    std::unordered_map<RenderTarget*, GLContext*> contexts;

    GLContext* getContext(RenderTarget* renderTarget);
    virtual void clear(Color color) override;
};

