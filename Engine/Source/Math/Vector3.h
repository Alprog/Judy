
#pragma once

#include "Containers/List.h"

#define __Meta__
#define __Serialize__

struct __Meta__ Vector3
{
    static const Vector3 Zero;
    static const Vector3 One;

    Vector3(float x = 0, float y = 0, float z = 0);

    __Serialize__ Vector3(List<float> list);
    __Serialize__ List<float> toList();

    float Length();
    float SquaredLength();

    friend Vector3 operator-(const Vector3& vector);
    friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
    friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);

    friend Vector3 operator*(const Vector3& vector, const float& value);

    float x, y, z;
};
