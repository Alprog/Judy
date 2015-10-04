
#pragma once

#include <string>
#include "Meta/TypeMeta.h"

#define __Meta__

struct __Meta__ Vector2
{
    static const Vector2 Zero;
    static const Vector2 One;

    Vector2();
    Vector2(float x, float y);

    float x, y;

    float Length();
    float SquaredLength();

    friend Vector2 operator-(const Vector2& vector);
    friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);

    friend Vector2 operator*(const Vector2& vector, const float& value);
};
