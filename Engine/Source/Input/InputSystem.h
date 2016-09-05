
#pragma once
#include "Singleton.h"
#include "InputDevice.h"
#include "Platform.h"

PLATFORM_FORWARD_DECLARE(InputSystem)

class InputSystem : public Singleton<InputSystem, PlatformInputSystem>
{
public:
    virtual void UpdateState() = 0;

protected:
    std::vector<InputDevice*> devices;
};
