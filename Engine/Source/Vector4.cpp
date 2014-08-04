
#include "Vector4.h"
#include "math.h"

float Vector4::Length()
{
    return sqrt(x * x + y * y + z * z + w * w);
}

float Vector4::SquaredLength()
{
    return x * x + y * y + z * z + w * w;
}

Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
{
    return
    {
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z,
        lhs.w + rhs.w
    };
}

Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
{
    return
    {
        lhs.x - rhs.x,
        lhs.y - rhs.y,
        lhs.z - rhs.z,
        lhs.w - rhs.w
    };
}
