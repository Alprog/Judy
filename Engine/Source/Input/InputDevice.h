
#pragma once

#include "InputDeviceType.h"
#include "Key.h"
#include "KeysState.h"

class [[Meta]] InputDevice
{
    friend class Meta;

public:
    InputDevice();

    virtual void updateState() = 0;

    bool isPressed(int keyCode);
    bool isReleased(int keyCode);
    bool wasPressed(int keyCode);
    bool wasReleased(int keyCode);
    bool onPressed(int keyCode);
    bool onReleased(int keyCode);

    InputDeviceType type;

    KeysState currentState;
    KeysState previousState;
};
