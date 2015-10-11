
#pragma once

#include "Containers/List.h"
#include "Attributes.h"

struct _(Meta)__ Vector3
{
    static const Vector3 Zero;
    static const Vector3 One;

    Vector3(float x = 0, float y = 0, float z = 0);

    _(Serialize)__ Vector3(List<float> list);
    _(Serialize)__ List<float> toList();

    float Length();
    float SquaredLength();

    friend Vector3 operator-(const Vector3& vector);
    friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
    friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);

    friend Vector3 operator*(const Vector3& vector, const float& value);

    _(Bind)__ float x, y, z;
};
