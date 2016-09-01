
#include <PlatformInputSystem.h>

#include <libevdev/libevdev.h>
#include <fcntl.h>
#include <errno.h>"
#include <PlatformInputDevice.h>


int monitorFile;

LinuxInputSystem::LinuxInputSystem()
{    
    udev = udev_new();

    monitor = udev_monitor_new_from_netlink(udev, "udev");
    udev_monitor_filter_add_match_subsystem_devtype(monitor, "input", nullptr);
    udev_monitor_enable_receiving(monitor);
    monitorFile = udev_monitor_get_fd(monitor);

    RegisterAllDevices();
}

LinuxInputSystem::~LinuxInputSystem()
{
}

void LinuxInputSystem::RegisterAllDevices()
{
    auto udevenum = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(udevenum, "input");
    udev_enumerate_scan_devices(udevenum);

    udev_list_entry* entry = udev_enumerate_get_list_entry(udevenum);
    for (; entry != nullptr; entry = udev_list_entry_get_next(entry))
    {
        auto path = udev_list_entry_get_name(entry);

        auto udevDevice = udev_device_new_from_syspath(udev, path);

        auto devNode = udev_device_get_devnode(udevDevice);
        if (devNode != nullptr)
        {
            std::string filePath = devNode;
            if (filePath.find("event") != std::string::npos)
            {
                auto serial = udev_device_get_property_value(udevDevice, "ID_SERIAL");

                bool isMouse = udev_device_get_property_value(udevDevice, "ID_INPUT_MOUSE") != nullptr;
                bool isKeyboard = udev_device_get_property_value(udevDevice, "ID_INPUT_KEYBOARD") != nullptr;
                bool isGamepad = udev_device_get_property_value(udevDevice, "ID_INPUT_JOYSTICK") != nullptr;
                bool isKey = udev_device_get_property_value(udevDevice, "ID_INPUT_KEY") != nullptr;

                bool isKnownDevice = isMouse || isKeyboard || isGamepad || (isKey && serial != nullptr);
                if (isKnownDevice)
                {
                    TryAddDevice(filePath);
                }
            }
        }

        udev_device_unref(udevDevice);
    }
}

void LinuxInputSystem::TryAddDevice(std::string filePath)
{
    auto device = PlatformInputDevice::Create(filePath);
    if (device != nullptr)
    {
        printf(">> %s\n", filePath.c_str());

        devices.push_back(device);
    }
}

void LinuxInputSystem::TryRemoveDevice(std::string filePath)
{
    for (auto it = std::begin(devices); it != std::end(devices);)
    {
        if (static_cast<PlatformInputDevice*>(*it)->filePath == filePath)
        {
            delete *it;
            it = devices.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void LinuxInputSystem::CheckHotPlugs()
{
    fd_set fileSet;
    FD_ZERO(&fileSet);
    FD_SET(monitorFile, &fileSet);

    static timeval timeout = {0};

    auto result = select(monitorFile + 1, &fileSet, nullptr, nullptr, &timeout);

    if (result > 0)
    {
        auto dev = udev_monitor_receive_device(monitor);
        if (dev)
        {
            const char* filePath = udev_device_get_devnode(dev);
            if (filePath != nullptr)
            {
                std::string action = udev_device_get_action(dev);
                if (action == "add")
                {
                    TryAddDevice(filePath);
                }
                else if (action == "remove")
                {
                    TryRemoveDevice(filePath);
                }
            }
        }
    }
}

