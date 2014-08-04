
#pragma once

struct Vector4
{
    float x;
    float y;
    float z;
    float w;

    float Length();
    float SquaredLength();

    friend Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
    friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
};
