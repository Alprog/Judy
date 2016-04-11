
#pragma once

#include "RenderTarget.h"
#include "Color.h"
#include "Quad.h"

#include "Mesh.h"
#include "RenderState.h"
#include "Math/Matrix.h"
#include <unordered_map>

class Node;
class Texture;
class Shader;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;

class Renderer
{
public:
    virtual ~Renderer() {}

    std::unordered_map<std::string, void*> textures;

    virtual void DrawQuad(Quad* quad) = 0;

    virtual void Draw(Mesh* mesh, Matrix matrix, RenderState* renderState) = 0;

    virtual void Render(Node* scene, RenderTarget* target) = 0;
    virtual void Clear(Color color) = 0;

    virtual void* CreateImpl(Texture* resource) = 0;
    virtual void* CreateImpl(VertexBuffer* resource) = 0;
    virtual void* CreateImpl(IndexBuffer* resource) = 0;
    virtual void* CreateImpl(Shader* resource) = 0;
    virtual void* CreateImpl(ConstantBuffer* resource) = 0;
};
