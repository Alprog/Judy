
#pragma once

#include "RenderTarget.h"
#include "Color.h"
#include "Quad.h"

#include "Mesh.h"
#include "Material.h"
#include "Math/Matrix.h"

class Node;

#include <unordered_map>

class Renderer
{
public:
    std::unordered_map<std::string, void*> textures;

    virtual void DrawQuad(Quad* quad) = 0;

    virtual void Draw(Mesh* mesh, Material* material, Matrix matrix) = 0;

    virtual void Render(Node* scene, RenderTarget* target) = 0;
    virtual void Clear(Color color) = 0;
};
