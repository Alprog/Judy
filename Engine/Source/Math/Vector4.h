
#pragma once

struct Vector4
{
    static const Vector4 Zero;
    static const Vector4 One;

    float x;
    float y;
    float z;
    float w;

    float Length();
    float SquaredLength();

    friend Vector4 operator-(const Vector4& vector);
    friend Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
    friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
};
