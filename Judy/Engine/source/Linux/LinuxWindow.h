
#pragma once

#include "Window.h"

class LinuxWindow : Window
{
public:
    LinuxWindow();

    virtual void ProcessEvents();

    virtual void SetContext();
    virtual void Swap();
};
