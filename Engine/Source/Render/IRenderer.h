
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

class Node;
class Texture;
class Shader;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
struct RenderCommand;

class IRenderer
{
public:
    virtual ~IRenderer() {}

    void Render(Node* scene, RenderTarget* target);
    virtual void Render(std::vector<RenderCommand> commands, RenderTarget* target) = 0;
    virtual void Draw(RenderCommand renderCommand) = 0;

    virtual void Clear(Color color) = 0;

    virtual void CreateImpl(Texture* resource) = 0;
    virtual void CreateImpl(VertexBuffer* resource) = 0;
    virtual void CreateImpl(IndexBuffer* resource) = 0;
    virtual void CreateImpl(Shader* resource) = 0;
    virtual void CreateImpl(ConstantBuffer* resource) = 0;
};
