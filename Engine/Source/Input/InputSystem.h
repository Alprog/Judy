
#pragma once
#include "Singleton.h"
#include "InputDevice.h"
#include <Windows.h>

class InputSystem : public Singleton<InputSystem>
{
    friend class Singleton<InputSystem>;

private:
    InputSystem();

public:
    void UpdateState();

    std::vector<InputDevice> devices;

    HWND hWnd;
};
