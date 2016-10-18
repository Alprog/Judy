
#pragma once

#include "Containers/List.h"
#include "Attributes.h"

class [[Meta]] Quaternion
{
public:
    static const Quaternion Identity;

    Quaternion(float x = 0, float y = 0, float z = 0, float w = 1);

    [[Serialize]] Quaternion(List<float> list);
    [[Serialize]] List<float> ToList();

    static Quaternion YawPitchRoll(float yaw, float pitch, float roll);

    [[Bind]] float x, y, z, w;
};
