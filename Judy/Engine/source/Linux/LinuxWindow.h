
#pragma once
#include "Window.h"

class LinuxWindow : JWindow
{
public:
    LinuxWindow();

    virtual void SetContext();
    virtual void Swap();
};
