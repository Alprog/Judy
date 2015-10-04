
#pragma once

#include "Containers/List.h"

#define __Meta__
#define __Serialize__

struct __Meta__ Vector4
{
    static const Vector4 Zero;
    static const Vector4 One;

    Vector4(float x = 0, float y = 0, float z = 0, float w = 0);

    Vector4(List<Any> list);
    __Serialize__ List<Any> toList();

    float Length();
    float SquaredLength();

    friend Vector4 operator-(const Vector4& vector);
    friend Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
    friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);

    friend Vector4 operator*(const Vector4& vector, const float& value);

    float x, y, z, w;
};
