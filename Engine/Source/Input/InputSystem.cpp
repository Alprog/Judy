
#include <InputSystem.h>
#include <PlatformInputSystem.h>

#include <Singleton.tpp>
template class Singleton<InputSystem, PlatformInputSystem>;

void InputSystem::UpdateState()
{
    CheckHotPlugs();

    for (auto device : devices)
    {
        device->UpdateState();
    }
}
