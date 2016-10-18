
#pragma once

#include <InputDevice.h>

class WinInputDevice : public InputDevice
{
public:
    virtual void updateState() override
    {
    }
};

using PlatformInputDevice = WinInputDevice;
