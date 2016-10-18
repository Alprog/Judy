
#include <KeysState.h>

bool KeysState::isSet(int keyCode)
{
    if (keyCode < KEY_COUNT)
    {
        return knownKeys[keyCode];
    }
    else
    {
        return unknownKeys.find(keyCode) != std::end(unknownKeys);
    }
}

void KeysState::set(int keyCode)
{
    if (keyCode < KEY_COUNT)
    {
        knownKeys[keyCode] = true;
    }
    else
    {
        unknownKeys.insert(keyCode);
    }
}

void KeysState::unset(int keyCode)
{
    if (keyCode < KEY_COUNT)
    {
        knownKeys[keyCode] = false;
    }
    else
    {
        unknownKeys.erase(keyCode);
    }
}
