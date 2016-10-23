
#pragma once

#include "SingletonObject.h"
#include "InputDevice.h"
#include "Platform.h"

PLATFORM_FORWARD_DECLARE(InputSystem)

class [[Meta]] InputSystem : public SingletonObject<InputSystem, PlatformInputSystem>
{
    friend class Meta;

public:
    virtual void updateState() = 0;

    bool isPressed(int keyCode);
    bool onPressed(int keyCode);

protected:
    std::vector<InputDevice*> devices;
};
