
#pragma once

#include "Vector2.h"
#include "Matrix.h"

struct Transform
{
    Vector3 Pivot;
    Vector3 Translation;
    float Rotation;
    Vector3 Scaling;

    Transform();

    Matrix GetMatrix();
};
