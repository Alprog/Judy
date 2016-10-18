
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

    [[Bind]] void addKeySource(int index, InputDevice* device, int keyCode);

    [[Bind]] bool isPressed(int index);
    [[Bind]] bool isReleased(int index);
    [[Bind]] bool wasPressed(int index);
    [[Bind]] bool wasReleased(int index);
    [[Bind]] bool onPressed(int index);
    [[Bind]] bool onReleased(int index);

    std::vector<std::vector<Source>> keys;
};
