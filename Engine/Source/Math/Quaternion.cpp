
#include "Quaternion.h"
#include "math.h"

const Quaternion Quaternion::Identity {0, 0, 0, 1};

Quaternion::Quaternion(float x, float y, float z, float w)
    : x{x}
    , y{y}
    , z{z}
    , w{w}
{
}

Quaternion::Quaternion(List<float> list)
    : x{list[0]}
    , y{list[1]}
    , z{list[2]}
    , w{list[3]}
{
}

List<float> Quaternion::toList()
{
    return {x, y, z, w};
}

Quaternion Quaternion::yawPitchRoll(float yaw, float pitch, float roll) // Euler sequence 2; -1; -3
{
    auto c1 = cos(yaw / 2);
    auto s1 = sin(yaw / 2);
    auto c2 = cos(-pitch / 2);
    auto s2 = sin(-pitch / 2);
    auto c3 = cos(-roll / 2);
    auto s3 = sin(-roll / 2);

    return
    {
        s1 * c2 * s3 + c1 * s2 * c3,
        s1 * c2 * c3 - c1 * s2 * s3,
       -s1 * s2 * c3 + c1 * c2 * s3,
        s1 * s2 * s3 + c1 * c2 * c3,
    };
}
