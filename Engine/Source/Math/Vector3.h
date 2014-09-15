
#pragma once

struct Vector3
{
    static const Vector3 Zero;
    static const Vector3 One;

    Vector3(float x = 0, float y = 0, float z = 0);

    float x;
    float y;
    float z;

    float Length();
    float SquaredLength();

    friend Vector3 operator-(const Vector3& vector);
    friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
    friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
};
