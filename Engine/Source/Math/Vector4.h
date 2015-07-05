
#pragma once

#define __Meta__
#define __Serialized__


struct __Meta__ Vector4
{
    static const Vector4 Zero;
    static const Vector4 One;

    Vector4(float x = 0, float y = 0, float z = 0, float w = 0);

    float __Serialized__  x;
    __Serialized__ float y;
    __Serialized__ float z, w;

    float Length();
    float SquaredLength();

    friend Vector4 operator-(const Vector4& vector);
    friend Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
    friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);

    static void a(char* a = "ff", char* b = "fefe\"gh");
};
