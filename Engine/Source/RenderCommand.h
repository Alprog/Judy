
#pragma once

#include <Matrix.h>
#include "Mesh.h"
#include "RenderState.h"

class RenderCommand
{
    Mesh* mesh;
    Matrix matrix;
    RenderState* state;
};
