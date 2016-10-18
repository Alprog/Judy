
#pragma once

#include <bitset>
#include <set>
#include <Key.h>

constexpr int KEY_COUNT = static_cast<int>(Key::COUNT);

class KeysState
{
public:
    bool isSet(int keyCode);
    void set(int keyCode);
    void unset(int keyCode);

private:
    std::bitset<KEY_COUNT> knownKeys;
    std::set<int> unknownKeys;
};
