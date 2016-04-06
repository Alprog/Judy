
#pragma once

#include "RenderTarget.h"
#include "Color.h"
#include "Quad.h"

#include "Mesh.h"
#include "RenderState.h"
#include "Math/Matrix.h"
#include <unordered_map>

class Node;
class Image;
class Shader;

class Renderer
{
public:
    virtual ~Renderer() {}

    std::unordered_map<std::string, void*> textures;

    virtual void DrawQuad(Quad* quad) = 0;

    virtual void Draw(Mesh* mesh, Matrix matrix, RenderState* renderState) = 0;

    virtual void Render(Node* scene, RenderTarget* target) = 0;
    virtual void Clear(Color color) = 0;

    virtual void* CreateTexture(Image* image) = 0;
    virtual void* CreateShader(Shader* shader) = 0;
};
