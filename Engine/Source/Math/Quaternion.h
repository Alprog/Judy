
#pragma once

class Quaternion
{
public:
    static const Quaternion Identity;

    float x, y, z, w;

    Quaternion(float x = 0, float y = 0, float z = 0, float w = 1);
};
