
#pragma once
#include "Singleton.h"
#include "InputDevice.h"
#include "Platform.h"

PLATFORM_FORWARD_DECLARE(InputSystem)

class [[Meta]] InputSystem : public Singleton<InputSystem, PlatformInputSystem>
{
    friend class Meta;

public:
    virtual void UpdateState() = 0;

protected:
    std::vector<InputDevice*> devices;
};
