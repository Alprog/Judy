
#pragma once
#include "Singleton.h"
#include "InputDevice.h"

class InputSystem
{
public:
    static InputSystem* const Instance();

public:
    virtual void UpdateState() = 0;

    std::vector<InputDevice> devices;
};
