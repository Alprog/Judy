
#include <VirtualDevice.h>
#include <InputDevice.h>

VirtualDevice::VirtualDevice()
{

}

void VirtualDevice::AddKeySource(int index, InputDevice* device, int keyCode)
{
    if (index >= Keys.size())
    {
        Keys.resize(index + 1);
    }

    if (device != nullptr)
    {
        Keys[index].push_back({device, keyCode});
    }
}

bool VirtualDevice::IsPressed(int index)
{
    if (index >= Keys.size())
    {
        auto & sources = Keys[index];
        for (Source & source : sources)
        {
            if (source.device->IsPressed(source.keyCode))
            {
                return true;
            }
        }
    }
    return false;
}

bool VirtualDevice::IsReleased(int index)
{
    return !IsPressed(index);
}

bool VirtualDevice::WasPressed(int index)
{
    if (index >= Keys.size())
    {
        auto & sources = Keys[index];
        for (Source & source : sources)
        {
            if (source.device->WasPressed(source.keyCode))
            {
                return true;
            }
        }
    }
    return false;
}

bool VirtualDevice::WasReleased(int index)
{
    return !WasPressed(index);
}

bool VirtualDevice::OnPressed(int index)
{
    return !WasPressed(index) && IsPressed(index);
}

bool VirtualDevice::OnReleased(int index)
{
    return WasPressed(index) && !IsPressed(index);
}
