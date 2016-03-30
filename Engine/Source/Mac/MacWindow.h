
#pragma once
#include "Window.h"

class MacWindow : public WindowM
{
public:
    MacWindow();

    virtual void ProcessEvents();
    virtual void SetContext();
    virtual void Swap();

private:
};
