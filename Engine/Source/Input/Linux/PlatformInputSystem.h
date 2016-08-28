
#pragma once
#include <InputSystem.h>
#include <Key.h>
#include <libudev.h>

class LinuxInputSystem : public InputSystem
{
    friend SingletonType;

private:
    LinuxInputSystem();
    ~LinuxInputSystem();

protected:
    virtual void CheckHotPlugs() override;

private:
    void RegisterAllDevices();
    void TryAddDevice(std::string filePath);
    void TryRemoveDevice(std::string filePath);

    udev* udev;
    udev_monitor* monitor;
    int monitorFile;
};

using PlatformInputSystem = LinuxInputSystem;
