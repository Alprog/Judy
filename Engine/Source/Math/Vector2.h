
#pragma once

struct Vector2
{
    float x;
    float y;

    float Length();
    float SquaredLength();

    friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
};

