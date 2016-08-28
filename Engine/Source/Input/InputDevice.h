
#pragma once

#include "InputDeviceType.h"

class InputDevice
{
public:
    virtual void UpdateState() = 0;

    InputDeviceType Type;
};
