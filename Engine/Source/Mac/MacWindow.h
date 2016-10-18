
#pragma once
#include "Window.h"

class MacWindow : public Window
{
public:
    MacWindow();

    virtual void processEvents();
    virtual void setContext();
    virtual void swap();

private:
};
