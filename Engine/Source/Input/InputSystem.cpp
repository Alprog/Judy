
#include <InputSystem.h>
#include <PlatformInputSystem.h>

#include <Singleton.tpp>
template class Singleton<InputSystem, PlatformInputSystem>;

bool InputSystem::isPressed(int keyCode)
{
    for (auto device : devices)
    {
        if (device->isPressed(keyCode))
        {
            return true;
        }
    }
    return false;
}

bool InputSystem::onPressed(int keyCode)
{
    for (auto device : devices)
    {
        if (device->onPressed(keyCode))
        {
            return true;
        }
    }
    return false;
}
