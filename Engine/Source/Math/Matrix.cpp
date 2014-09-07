
#include "Matrix.h"
#include "math.h"

const Matrix Matrix::Identity =
{
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 1, 0, 1
};

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
    return // mij = mi1*m1j + mi2*m2j + mi3*m3j + mi4*m4j
    {
        lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21 + lhs.m13 * rhs.m31 + lhs.m14 * rhs.m41,
        lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22 + lhs.m13 * rhs.m32 + lhs.m14 * rhs.m42,
        lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13 * rhs.m33 + lhs.m14 * rhs.m43,
        lhs.m11 * rhs.m14 + lhs.m12 * rhs.m24 + lhs.m13 * rhs.m34 + lhs.m14 * rhs.m44,

        lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21 + lhs.m23 * rhs.m31 + lhs.m24 * rhs.m41,
        lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 + lhs.m23 * rhs.m32 + lhs.m24 * rhs.m42,
        lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 + lhs.m23 * rhs.m33 + lhs.m24 * rhs.m43,
        lhs.m21 * rhs.m14 + lhs.m22 * rhs.m24 + lhs.m23 * rhs.m34 + lhs.m24 * rhs.m44,

        lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 + lhs.m33 * rhs.m31 + lhs.m34 * rhs.m41,
        lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 + lhs.m33 * rhs.m32 + lhs.m34 * rhs.m42,
        lhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33 * rhs.m33 + lhs.m34 * rhs.m43,
        lhs.m31 * rhs.m14 + lhs.m32 * rhs.m24 + lhs.m33 * rhs.m34 + lhs.m34 * rhs.m44,

        lhs.m41 * rhs.m11 + lhs.m42 * rhs.m21 + lhs.m43 * rhs.m31 + lhs.m44 * rhs.m41,
        lhs.m41 * rhs.m12 + lhs.m42 * rhs.m22 + lhs.m43 * rhs.m32 + lhs.m44 * rhs.m42,
        lhs.m41 * rhs.m13 + lhs.m42 * rhs.m23 + lhs.m43 * rhs.m33 + lhs.m44 * rhs.m43,
        lhs.m41 * rhs.m14 + lhs.m42 * rhs.m24 + lhs.m43 * rhs.m34 + lhs.m44 * rhs.m44
    };
}

Matrix& Matrix::operator*=(const Matrix& rhs)
{
    // mij = mi1*m1j + mi2*m2j + mi3*m3j + mi4*m4j

    m11 = m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31 + m14 * rhs.m41;
    m12 = m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32 + m14 * rhs.m42;
    m13 = m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33 + m14 * rhs.m43;
    m14 = m11 * rhs.m14 + m12 * rhs.m24 + m13 * rhs.m34 + m14 * rhs.m44;

    m21 = m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31 + m24 * rhs.m41;
    m22 = m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32 + m24 * rhs.m42;
    m23 = m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33 + m24 * rhs.m43;
    m24 = m21 * rhs.m14 + m22 * rhs.m24 + m23 * rhs.m34 + m24 * rhs.m44;

    m31 = m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31 + m34 * rhs.m41;
    m32 = m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32 + m34 * rhs.m42;
    m33 = m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33 + m34 * rhs.m43;
    m34 = m31 * rhs.m14 + m32 * rhs.m24 + m33 * rhs.m34 + m34 * rhs.m44;

    m41 = m41 * rhs.m11 + m42 * rhs.m21 + m43 * rhs.m31 + m44 * rhs.m41;
    m42 = m41 * rhs.m12 + m42 * rhs.m22 + m43 * rhs.m32 + m44 * rhs.m42;
    m43 = m41 * rhs.m13 + m42 * rhs.m23 + m43 * rhs.m33 + m44 * rhs.m43;
    m44 = m41 * rhs.m14 + m42 * rhs.m24 + m43 * rhs.m34 + m44 * rhs.m44;

    return *this;
}

Matrix Matrix::Translation(Vector3 t)
{
    return
    {
        1,   0,   0,   0,
        0,   1,   0,   0,
        0,   0,   1,   0,
       t.x, t.y, t.z,  1
    };
}

Matrix Matrix::RotationX(float r)
{
    float c = cos(r);
    float s = sin(r);

    return
    {
        1,  0,  0,  0,
        0, +c, +s,  0,
        0, -s, +c,  0,
        0,  0,  0,  1
    };
}

Matrix Matrix::RotationY(float r)
{
    float c = cos(r);
    float s = sin(r);

    return
    {
       +c,  0, -s,  0,
        0,  1,  0,  0,
       +s,  0, +c,  0,
        0,  0,  0,  1
    };
}

Matrix Matrix::RotationZ(float r)
{
    float c = cos(r);
    float s = sin(r);

    return
    {
       +c, +s,  0,  0,
       -s, +c,  0,  0,
        0,  0,  1,  0,
        0,  0,  0,  1
    };
}

Matrix Matrix::Scaling(Vector3 s)
{
    return
    {
       s.x,  0,   0,   0,
        0,  s.y,  0,   0,
        0,   0,  s.z,  0,
        0,   0,   0,   1
    };
}

