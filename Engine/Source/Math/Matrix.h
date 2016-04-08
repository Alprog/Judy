
#pragma once

#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Attributes.h"

struct Matrix
{
    static const Matrix Identity;

    union
    {
        struct // row-major
        {
            float m11, m12, m13, m14;
            float m21, m22, m23, m24;
            float m31, m32, m33, m34;
            float m41, m42, m43, m44;
        };

        float m[4][4]; // [row][column]
    };

    static Matrix Translation(Vector3 translation);
    static Matrix Rotation(Quaternion rotation);
    static Matrix RotationX(float rotation);
    static Matrix RotationY(float rotation);
    static Matrix RotationZ(float rotation);
    static Matrix Scaling(Vector3 scaling);

    static Matrix TRS(Vector3& translation, Quaternion& rotation, Vector3& scaling);

    static Matrix OrthographicLH(float width, float height, float znear, float zfar);
    static Matrix OrthographicLH(float left, float right, float bottom, float top, float znear, float zfar);

    friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);

    friend Vector4 operator*(const Vector3& lhs, const Matrix& rhs);

    Matrix& operator*=(const Matrix& rhs);
};
