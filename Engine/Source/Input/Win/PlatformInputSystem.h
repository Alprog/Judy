
#pragma once
#include <InputSystem.h>
#include <Windows.h>
#include <Key.h>

class WinInputSystem : public InputSystem
{
    friend class SingletonType;

private:
    WinInputSystem();
    ~WinInputSystem();

public:
    virtual void updateState() override;

    std::vector<Key> keys;

    void initKeys();
    void findDevices();

private:
    HWND hWnd;
};

using PlatfromInputSystem = WinInputSystem;
