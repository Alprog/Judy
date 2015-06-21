
#pragma once

#define __Meta__
#define __Serialized__


struct __Meta__ Vector4
{
    static const Vector4 Zero;
    static const Vector4 One;

    Vector4(float x = 0, float y = 0, float z = 0, float w = 0);

    __Serialized__ float x;
    __Serialized__ float y;
    __Serialized__ float z;
    __Serialized__ float w;

    float Length();
    float SquaredLength();

    friend Vector4 operator-(const Vector4& vector);
    friend Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
    friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
};
