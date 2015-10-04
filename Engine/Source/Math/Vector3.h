
#pragma once

#define __Meta__
#define __Serialized__

struct __Meta__ Vector3
{
    static const Vector3 Zero;
    static const Vector3 One;

    Vector3(float x = 0, float y = 0, float z = 0);

    __Serialized__ float x, y, z;

    float Length();
    float SquaredLength();

    friend Vector3 operator-(const Vector3& vector);
    friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
    friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);

    friend Vector3 operator*(const Vector3& vector, const float& value);
};
