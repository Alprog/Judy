
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
    virtual void UpdateState() override;

    std::vector<Key> keys;

    void InitKeys();
    void FindDevices();

private:
    HWND hWnd;
};
