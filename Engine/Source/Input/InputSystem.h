
#pragma once

#include "Singleton.h"
#include "InputDevice.h"
#include "Platform.h"
#include <vector>

PLATFORM_FORWARD_DECLARE(InputSystem)

class [[Meta]] InputSystem : public Singleton<InputSystem, PlatformInputSystem>
{
    friend class Meta;

public:
    virtual void updateState() = 0;

    bool isPressed(int keyCode);
    bool onPressed(int keyCode);

protected:
    std::vector<InputDevice*> devices;
};
