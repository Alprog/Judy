
#pragma once

#include "Node.h"

#include "Mesh.h"
#include "Render/RenderState.h"
#include "Render/IRenderer.h"
#include "Attributes.h"

struct [[Meta]] Model : public Node
{
    Model();

    virtual void render(Matrix matrix, RendererFrontend* renderer) override;

    Mesh* mesh;
    RenderState* renderState;

    [[Serialize, Inspect]] std::string name;
};
