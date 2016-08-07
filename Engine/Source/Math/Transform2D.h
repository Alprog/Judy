
#pragma once

#include "Vector2.h"
#include "Matrix.h"

struct Transform2D
{
    Vector3 Pivot;
    Vector3 Translation;
    float Rotation;
    Vector3 Scaling;

    Transform2D();

    Matrix GetMatrix();
};
