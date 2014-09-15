
#pragma once

#define META(_)
#define SERIALIZED

META(Serialize)
struct Vector4
{
    static const Vector4 Zero;
    static const Vector4 One;

    Vector4(float x = 0, float y = 0, float z = 0, float w = 0);

    SERIALIZED float x;
    SERIALIZED float y;
    SERIALIZED float z;
    SERIALIZED float w;

    float Length();
    float SquaredLength();

    friend Vector4 operator-(const Vector4& vector);
    friend Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
    friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
};
