
#pragma once

#include "Containers/List.h"

#define __Meta__
#define __Serialize__

class __Meta__ Quaternion
{
public:
    static const Quaternion Identity;

    Quaternion(float x = 0, float y = 0, float z = 0, float w = 1);

    __Serialize__ Quaternion(List<Any> list);
    __Serialize__ List<Any> toList();

    static Quaternion YawPitchRoll(float yaw, float pitch, float roll);

    float x, y, z, w;
};
