
#include "InputDevice.h"

constexpr int KeyCount = static_cast<int>(Key::COUNT);

InputDevice::InputDevice()
{
}

void InputDevice::updateState()
{
    previousState = currentState;
}

bool InputDevice::isPressed(int keyCode)
{
    return currentState.isSet(keyCode);
}

bool InputDevice::isReleased(int keyCode)
{
    return !currentState.isSet(keyCode);
}

bool InputDevice::wasPressed(int keyCode)
{
    return previousState.isSet(keyCode);
}

bool InputDevice::wasReleased(int keyCode)
{
    return !previousState.isSet(keyCode);
}

bool InputDevice::onPressed(int keyCode)
{
    return !previousState.isSet(keyCode) && currentState.isSet(keyCode);
}

bool InputDevice::onReleased(int keyCode)
{
    return previousState.isSet(keyCode) && !currentState.isSet(keyCode);
}
