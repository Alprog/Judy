
#pragma once

#include "RenderTarget.h"
#include "Color.h"
#include "Quad.h"

#include "Mesh.h"
#include "RenderState.h"
#include "RendererType.h"
#include "Math/Matrix.h"
#include <unordered_map>
#include "RenderCommand.h"
#include "Renderer.h"

class Node;
class Texture;
class Shader;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class PipelineState;
struct RenderCommand;

class [[Meta]] IRenderer : public Object
{
public:
    virtual ~IRenderer() {}

    [[Ignore]] void render(Node* scene, RenderTarget* target);
    [[Ignore]] virtual void render(std::vector<RenderCommand> commands, RenderTarget* target) = 0;
    [[Ignore]] virtual void draw(RenderCommand renderCommand) = 0;

    [[Ignore]] virtual void clear(Color color) = 0;

    [[Ignore]] virtual void createImpl(Texture* resource) = 0;
    [[Ignore]] virtual void createImpl(VertexBuffer* resource) = 0;
    [[Ignore]] virtual void createImpl(IndexBuffer* resource) = 0;
    [[Ignore]] virtual void createImpl(Shader* resource) = 0;
    [[Ignore]] virtual void createImpl(ConstantBuffer* resource) = 0;
    [[Ignore]] virtual void createImpl(PipelineState* resource) = 0;

    virtual RendererType getType() = 0;
};
