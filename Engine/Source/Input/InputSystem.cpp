
#include "InputSystem.h"
#include "Platforms.h"

InputSystem* const InputSystem::Instance()
{
    static PlatformInputSystem inputSystem;
    return &inputSystem;
}
