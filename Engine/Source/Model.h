
#pragma once

#include "Node.h"

#include "Mesh.h"
#include "Material.h"
#include "Renderer.h"

struct Model : public Node
{
    Model();

    virtual void Update(double delta) override;
    virtual void Render(Matrix matrix,Renderer* renderer) override;

    Mesh* mesh;
    Material* material;
};
