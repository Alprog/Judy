
#pragma once

#include "InputDeviceType.h"
#include "Key.h"
#include "KeysState.h"

class [[Meta]] InputDevice
{
    friend class Meta;

public:
    InputDevice();

    virtual void UpdateState() = 0;

    bool IsPressed(int keyCode);
    bool IsReleased(int keyCode);
    bool WasPressed(int keyCode);
    bool WasReleased(int keyCode);
    bool OnPressed(int keyCode);
    bool OnReleased(int keyCode);

    InputDeviceType type;

    KeysState currentState;
    KeysState previousState;
};
