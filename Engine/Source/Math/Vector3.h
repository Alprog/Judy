
#pragma once

struct Vector3
{
    static const Vector3 Zero;
    static const Vector3 One;

    float x;
    float y;
    float z;

    float Length();
    float SquaredLength();

    friend Vector3 operator-(const Vector3& vector);
    friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
    friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
};
