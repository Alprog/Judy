
#pragma once

#include <string>
#include "Meta/TypeMeta.h"
#include "Containers/List.h"
#include "Attributes.h"

struct _(Meta)__ Vector2
{
    static const Vector2 Zero;
    static const Vector2 One;

    Vector2();
    Vector2(float x, float y);

    _(Serialize)__ Vector2(List<float> list);
    _(Serialize)__ List<float> toList();

    float Length();
    float SquaredLength();

    friend Vector2 operator-(const Vector2& vector);
    friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);

    friend Vector2 operator*(const Vector2& vector, const float& value);

    float x, y;
};
