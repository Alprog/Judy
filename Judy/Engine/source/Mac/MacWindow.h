
#pragma once
#include "Window.h"

class MacWindow : Window
{
public:
    MacWindow();

    virtual void ProcessEvents();
    virtual void SetContext();
    virtual void Swap();

private:
};
