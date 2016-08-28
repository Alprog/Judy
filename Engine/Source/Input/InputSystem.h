
#pragma once
#include "Singleton.h"
#include "InputDevice.h"
#include "Platform.h"

PLATFORM_FORWARD_DECLARE(InputSystem)

class InputSystem : public Singleton<InputSystem, PlatformInputSystem>
{
public:
    void UpdateState();

protected:
    virtual void CheckHotPlugs() = 0;

    std::vector<InputDevice*> devices;
};
