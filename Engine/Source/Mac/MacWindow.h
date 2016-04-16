
#pragma once
#include "Window.h"

class MacWindow : public Window
{
public:
    MacWindow();

    virtual void ProcessEvents();
    virtual void SetContext();
    virtual void Swap();

private:
};
