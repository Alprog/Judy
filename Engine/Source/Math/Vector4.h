
#pragma once

#include "Containers/List.h"
#include "Attributes.h"

struct _(Meta)__ Vector4
{
    static const Vector4 Zero;
    static const Vector4 One;

    Vector4(float x = 0, float y = 0, float z = 0, float w = 0);

    Vector4(List<float> list);
    _(Serialize)__ List<float> toList();

    float Length();
    float SquaredLength();

    friend Vector4 operator-(const Vector4& vector);
    friend Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
    friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);

    friend Vector4 operator*(const Vector4& vector, const float& value);

    float x, y, z, w;
};
