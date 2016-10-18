
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
    virtual void updateState() override;
    void checkHotPlugs();

private:
    void registerAllDevices();
    void tryAddDevice(std::string filePath);
    void tryRemoveDevice(std::string filePath);

    udev* udev;
    udev_monitor* monitor;
    int monitorFile;
};

using PlatformInputSystem = LinuxInputSystem;
