
#pragma once

#include "Node.h"

#include "Mesh.h"
#include "Material.h"
#include "Renderer.h"
#include "Attributes.h"

struct _(Meta)__ Model : public Node
{
    Model();

    virtual void Update(double delta) override;
    virtual void Render(Matrix matrix, Renderer* renderer) override;

    Mesh* mesh;
    Material* material;

    _(Serialize, Inspect)__ std::string name;
};
