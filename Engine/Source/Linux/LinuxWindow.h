
#pragma once

#include "Window.h"

class LinuxWindow : public Window
{
public:
    LinuxWindow();

    virtual void ProcessEvents();

    virtual void SetContext();
    virtual void Swap();
};
