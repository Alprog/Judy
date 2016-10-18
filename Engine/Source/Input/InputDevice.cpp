
#include "InputDevice.h"

constexpr int KeyCount = static_cast<int>(Key::COUNT);

InputDevice::InputDevice()
{
}

void InputDevice::UpdateState()
{
    previousState = currentState;
}

bool InputDevice::IsPressed(int keyCode)
{
    return currentState.IsSet(keyCode);
}

bool InputDevice::IsReleased(int keyCode)
{
    return !currentState.IsSet(keyCode);
}

bool InputDevice::WasPressed(int keyCode)
{
    return previousState.IsSet(keyCode);
}

bool InputDevice::WasReleased(int keyCode)
{
    return !previousState.IsSet(keyCode);
}

bool InputDevice::OnPressed(int keyCode)
{
    return !previousState.IsSet(keyCode) && currentState.IsSet(keyCode);
}

bool InputDevice::OnReleased(int keyCode)
{
    return previousState.IsSet(keyCode) && !currentState.IsSet(keyCode);
}
