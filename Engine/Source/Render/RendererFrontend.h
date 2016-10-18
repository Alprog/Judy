
#pragma once

#include <vector>
#include <queue>
#include "Node.h"
#include "Mesh.h"
#include "Math/Matrix.h"
#include "Render/RenderState.h"
#include "RenderCommand.h"

struct Context
{
    Matrix View;
    Matrix Projection;
    Matrix ViewProjection;
};

class RendererFrontend
{
public:
    void render(Node* scene);
    void draw(Mesh* mesh, Matrix matrix, RenderState* renderState);

    std::queue<Context> contexts;
    std::vector<RenderCommand> commands;
};
