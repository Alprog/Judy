
#pragma once

#include <string>
#include "Meta/TypeMeta.h"
#include "Containers/List.h"

#define __Meta__
#define __Serialize__

struct __Meta__ Vector2
{
    static const Vector2 Zero;
    static const Vector2 One;

    Vector2();
    Vector2(float x, float y);

    Vector2(List<Any> list);
    __Serialize__ List<Any> toList();

    float Length();
    float SquaredLength();

    friend Vector2 operator-(const Vector2& vector);
    friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);

    friend Vector2 operator*(const Vector2& vector, const float& value);

    float x, y;
};
