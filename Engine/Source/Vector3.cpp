
#include "Vector3.h"
#include "math.h"

float Vector3::Length()
{
    return sqrt(x * x + y * y + z * z);
}

float Vector3::SquaredLength()
{
    return x * x + y * y + z * z;
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    return
    {
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z
    };
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    return
    {
        lhs.x - rhs.x,
        lhs.y - rhs.y,
        lhs.z - rhs.z
    };
}
