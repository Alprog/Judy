
#include <VirtualDevice.h>
#include <InputDevice.h>

VirtualDevice::VirtualDevice()
{

}

void VirtualDevice::addKeySource(int index, InputDevice* device, int keyCode)
{
    if (index >= keys.size())
    {
        keys.resize(index + 1);
    }

    if (device != nullptr)
    {
        keys[index].push_back({device, keyCode});
    }
}

bool VirtualDevice::isPressed(int index)
{
    if (index >= keys.size())
    {
        auto & sources = keys[index];
        for (Source & source : sources)
        {
            if (source.device->isPressed(source.keyCode))
            {
                return true;
            }
        }
    }
    return false;
}

bool VirtualDevice::isReleased(int index)
{
    return !isPressed(index);
}

bool VirtualDevice::wasPressed(int index)
{
    if (index >= keys.size())
    {
        auto & sources = keys[index];
        for (Source & source : sources)
        {
            if (source.device->wasPressed(source.keyCode))
            {
                return true;
            }
        }
    }
    return false;
}

bool VirtualDevice::wasReleased(int index)
{
    return !wasPressed(index);
}

bool VirtualDevice::onPressed(int index)
{
    return !wasPressed(index) && isPressed(index);
}

bool VirtualDevice::onReleased(int index)
{
    return wasPressed(index) && !isPressed(index);
}
