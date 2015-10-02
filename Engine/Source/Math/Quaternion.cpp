
#include "Quaternion.h"

const Quaternion Quaternion::Identity {0, 0, 0, 1};

Quaternion::Quaternion(float x, float y, float z, float w)
    : x{x}
    , y{y}
    , z{z}
    , w{w}
{
}
