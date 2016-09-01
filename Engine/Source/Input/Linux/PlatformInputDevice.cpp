
#include <PlatformInputDevice.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

LinuxInputDevice* LinuxInputDevice::Create(std::string filePath)
{
    auto file = open(filePath.c_str(), O_RDONLY | O_NONBLOCK);
    if (file < 0)
    {
        if (errno == EACCES)
        {
            exit(0);
        }
        return nullptr;
    }

    libevdev* device;
    auto result = libevdev_new_from_fd(file, &device);
    if (result < 0)
    {
        close(file);
        return nullptr;
    }

    return new LinuxInputDevice(filePath, file, device);
}

LinuxInputDevice::LinuxInputDevice(std::string filePath, int file, libevdev* device)
{
    this->filePath = filePath;
    this->file = file;
    this->device = device;
}

LinuxInputDevice::~LinuxInputDevice()
{
    libevdev_free(device);
    close(file);
}

void LinuxInputDevice::UpdateState()
{
    input_event event;
    while (true)
    {
        auto result = libevdev_next_event(device, LIBEVDEV_READ_FLAG_NORMAL, &event);
        if (result == -EAGAIN)
        {
            break;
        }
        else if (result == LIBEVDEV_READ_STATUS_SYNC)
        {
            HandleSynDropped();
        }
        else if (result == LIBEVDEV_READ_STATUS_SUCCESS)
        {
            auto typeName = libevdev_event_type_get_name(event.type);
            auto codeName = libevdev_event_code_get_name(event.type, event.code);

            if (strcmp(typeName, "EV_SYN") == 0 || strcmp(typeName, "EV_REL") == 0 || strcmp(typeName, "EV_MSC") == 0 || strcmp(typeName, "EV_ABS") == 0)
                continue;

            printf("%s %s %i\n", typeName, codeName, event.value);
            fflush(stdout);
        }
        else
        {
            printf("error: %d\n", result);
            break;
        }
    }
}

void LinuxInputDevice::HandleSynDropped()
{
    input_event event;
    int result = 0;

    do
    {
        result = libevdev_next_event(device, LIBEVDEV_READ_FLAG_SYNC, &event);
        if (result < 0)
        {
            if (result != -EAGAIN)
            {
                printf("error %d\n", result);
            }
            return;
        }

        printf("State change since SYN_DROPPED for %s %s value %d\n",
                libevdev_event_type_get_name(event.type),
                libevdev_event_code_get_name(event.type, event.code),
                event.value);
    }
    while (result == LIBEVDEV_READ_STATUS_SYNC);
}
