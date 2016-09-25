
#include "InputDevice.h"

constexpr int KeyCount = static_cast<int>(Key::COUNT);

InputDevice::InputDevice()
{
}

void InputDevice::UpdateState()
{
    PreviousState = CurrentState;
}

bool InputDevice::IsPressed(int keyCode)
{
    return CurrentState.IsSet(keyCode);
}

bool InputDevice::IsReleased(int keyCode)
{
    return !CurrentState.IsSet(keyCode);
}

bool InputDevice::OnPressed(int keyCode)
{
    return !PreviousState.IsSet(keyCode) && CurrentState.IsSet(keyCode);
}

bool InputDevice::OnReleased(int keyCode)
{
    return PreviousState.IsSet(keyCode) && !CurrentState.IsSet(keyCode);
}
