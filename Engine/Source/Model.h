
#pragma once

#include "Node.h"

#include "Mesh.h"
#include "Material.h"
#include "Renderer.h"

#define __Meta__
#define __Serialize__

struct __Meta__ Model : public Node
{
    Model();

    virtual void Update(double delta) override;
    virtual void Render(Matrix matrix,Renderer* renderer) override;

    Mesh* mesh;
    Material* material;

    __Serialize__ std::string name;
};
