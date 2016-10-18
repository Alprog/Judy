
#pragma once

#include "Vector2.h"
#include "Matrix.h"

struct Transform2D
{
    Transform2D();

    Matrix GetMatrix();

    Vector3 pivot;
    Vector3 translation;
    float rotation;
    Vector3 scaling;
};
