
#pragma once

#include <vector>
#include "Mesh.h"
#include "Math/Matrix.h"
#include "Render/RenderState.h"
#include "RenderCommand.h"

class RendererFrontend
{
public:
    void Draw(Mesh* mesh, Matrix matrix, RenderState* renderState);

    std::vector<RenderCommand> commands;
};
