
#pragma once

#include <map>
#include <string>
#include <vector>
#include <Object.h>

class InputDevice;

class [[Meta]] VirtualDevice : public Object
{
    friend class Meta;

    VirtualDevice();

    struct Source
    {
        InputDevice* device;
        int keyCode;
    };

    std::vector<std::vector<Source>> Keys;

    [[Bind]] void AddKeySource(int index, InputDevice* device, int keyCode);

    [[Bind]] bool IsPressed(int index);
    [[Bind]] bool IsReleased(int index);
    [[Bind]] bool WasPressed(int index);
    [[Bind]] bool WasReleased(int index);
    [[Bind]] bool OnPressed(int index);
    [[Bind]] bool OnReleased(int index);
};
