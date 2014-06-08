
#pragma once
#include "Window.h"

class LinuxWindow : Window
{
public:
    LinuxWindow();

    virtual void SetContext();
    virtual void Swap();
};
