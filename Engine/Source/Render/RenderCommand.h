
#pragma once

#include "Math/Matrix.h"
#include "Mesh.h"
#include "RenderState.h"

struct RenderCommand
{
    Mesh* mesh;
    RenderState* state;
};
