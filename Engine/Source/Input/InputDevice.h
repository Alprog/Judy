
#pragma once

#include "InputDeviceType.h"
#include "Key.h"
#include "KeysState.h"

class InputDevice
{
public:
    InputDevice();

    virtual void UpdateState() = 0;

    bool IsPressed(int keyCode);
    bool IsReleased(int keyCode);
    bool OnPressed(int keyCode);
    bool OnReleased(int keyCode);

    InputDeviceType Type;

    KeysState CurrentState;
    KeysState PreviousState;
};
