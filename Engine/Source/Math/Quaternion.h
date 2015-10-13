
#pragma once

#include "Containers/List.h"
#include "Attributes.h"

class _(Meta)__ Quaternion
{
public:
    static const Quaternion Identity;

    Quaternion(float x = 0, float y = 0, float z = 0, float w = 1);

    _(Serialize)__ Quaternion(List<float> list);
    _(Serialize)__ List<float> toList();

    static Quaternion YawPitchRoll(float yaw, float pitch, float roll);

    _(Bind)__ float x, y, z, w;
};
