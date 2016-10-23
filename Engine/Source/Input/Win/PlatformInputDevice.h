
#pragma once

#include <InputDevice.h>
#include <windows.h>

class WinInputDevice : public InputDevice
{
public:
    virtual void updateState() override
    {
        previousState = currentState;
    }

    HANDLE handle;
};

using PlatformInputDevice = WinInputDevice;
