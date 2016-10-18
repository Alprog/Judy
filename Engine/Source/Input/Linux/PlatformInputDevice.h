
#pragma once

#include <InputDevice.h>
#include <libevdev/libevdev.h>
#include <string>

class LinuxInputDevice : public InputDevice
{
public:
    static LinuxInputDevice* create(std::string filePath);

private:
    LinuxInputDevice(std::string filePath, int file, libevdev* device);
    ~LinuxInputDevice();

public:
    virtual void updateState() override;

private:
    void handleSynDropped();

public:
    std::string filePath;
    int file;
    libevdev* device;
};

using PlatformInputDevice = LinuxInputDevice;
