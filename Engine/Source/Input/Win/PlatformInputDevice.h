
#pragma once

#include <InputDevice.h>

class WinInputDevice : public InputDevice
{
public:
    virtual void UpdateState() override
    {
    }
};

using PlatformInputDevice = WinInputDevice;
