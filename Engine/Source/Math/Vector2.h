
#pragma once

#include <string>
#include "Meta/TypeMeta.h"
#include "Containers/List.h"
#include "Attributes.h"

struct [[Meta]] Vector2
{
    static const Vector2 Zero;
    static const Vector2 One;

    Vector2();
    Vector2(float x, float y);

    [[Serialize]] Vector2(List<float> list);
    [[Serialize]] List<float> toList();

    float length();
    float squaredLength();

    friend Vector2 operator-(const Vector2& vector);
    friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);

    friend Vector2 operator*(const Vector2& vector, const float& value);

    [[Bind]] [[Inspect]] float x, y;
};
