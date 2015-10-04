
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

Quaternion Quaternion::YawPitchRoll(float yaw, float pitch, float roll)
{
   auto c1 = cos(yaw / 2);
   auto s1 = sin(yaw / 2);
   auto c2 = cos(pitch / 2);
   auto s2 = sin(pitch / 2);
   auto c3 = cos(roll / 2);
   auto s3 = sin(roll / 2);

   return
   {
       c1 * c2 * s3 + s1 * s2 * c3,
       s1 * c2 * c3 + c1 * s2 * s3,
       c1 * s2 * c3 - s1 * c2 * s3,
       c1 * c2 * c3 - s1 * s2 * s3
   };
}
