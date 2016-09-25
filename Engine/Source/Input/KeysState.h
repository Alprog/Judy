
#pragma once

#include <bitset>
#include <set>
#include <Key.h>

constexpr int KEY_COUNT = static_cast<int>(Key::COUNT);

class KeysState
{
public:
    bool IsSet(int keyCode);
    void Set(int keyCode);
    void Unset(int keyCode);

private:
    std::bitset<KEY_COUNT> KnownKeys;
    std::set<int> UnknownKeys;
};
