
#pragma once
#include "Singleton.h"
#include "InputDevice.h"

class InputSystem : public PlatformSingleton<InputSystem>
{
public:
    virtual void UpdateState() = 0;

    std::vector<InputDevice> devices;
};
