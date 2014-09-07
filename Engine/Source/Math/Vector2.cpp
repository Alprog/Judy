
#include "Vector2.h"
#include "math.h"

float Vector2::Length()
{
    return sqrt(x * x + y * y);
}

float Vector2::SquaredLength()
{
    return x * x + y * y;
}

Vector2 operator-(const Vector2& vector)
{
    return
    {
        -vector.x,
        -vector.y
    };
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
    return
    {
        lhs.x + rhs.x,
        lhs.y + rhs.y
    };
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
    return
    {
        lhs.x - rhs.x,
        lhs.y - rhs.y
    };
}
