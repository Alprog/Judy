
#pragma once
#include <InputSystem.h>
#include <Key.h>

class LinuxInputSystem : public InputSystem
{
    friend SingletonType;

private:
    LinuxInputSystem();
    ~LinuxInputSystem();

public:
    virtual void UpdateState() override;

};

using PlatformInputSystem = LinuxInputSystem;
