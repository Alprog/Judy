
#pragma once

template <typename T>
class Keyframe
{
public:
    Keyframe();

    int frame;
    T value;
};
