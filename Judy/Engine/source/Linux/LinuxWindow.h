
#pragma once
#include "Window.h"

namespace Judy
{
    class LinuxWindow : Window
    {
    public:
        LinuxWindow();

        virtual void SetContext();
        virtual void Swap();
    };
}
