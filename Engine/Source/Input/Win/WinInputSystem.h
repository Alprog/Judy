
#pragma once
#include <InputSystem.h>
#include <Windows.h>

class WinInputSystem : public InputSystem
{
    friend class InputSystem;

private:
    WinInputSystem();
    ~WinInputSystem();

public:
    virtual void UpdateState() override;

private:
    HWND hWnd;
};
