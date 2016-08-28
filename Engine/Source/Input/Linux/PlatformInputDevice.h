
#pragma once

#include <InputDevice.h>
#include <libevdev/libevdev.h>
#include <string>

class LinuxInputDevice : public InputDevice
{
public:
    static LinuxInputDevice* Create(std::string filePath);

private:
    LinuxInputDevice(std::string filePath, int file, libevdev* device);
    ~LinuxInputDevice();

public:
    virtual void UpdateState() override;

private:
    void HandleSynDropped();

public:
    std::string filePath;
    int file;
    libevdev* device;
};

using PlatformInputDevice = LinuxInputDevice;
