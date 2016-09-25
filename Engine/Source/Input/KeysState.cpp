
#include <KeysState.h>

bool KeysState::IsSet(int keyCode)
{
    if (keyCode < KEY_COUNT)
    {
        return KnownKeys[keyCode];
    }
    else
    {
        return UnknownKeys.find(keyCode) != std::end(UnknownKeys);
    }
}

void KeysState::Set(int keyCode)
{
    if (keyCode < KEY_COUNT)
    {
        KnownKeys[keyCode] = true;
    }
    else
    {
        UnknownKeys.insert(keyCode);
    }
}

void KeysState::Unset(int keyCode)
{
    if (keyCode < KEY_COUNT)
    {
        KnownKeys[keyCode] = false;
    }
    else
    {
        UnknownKeys.erase(keyCode);
    }
}
