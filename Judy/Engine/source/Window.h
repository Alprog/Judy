
#pragma once

#include "Context.h"
#include "Scene.h"

class Window
{
public:
    static Window* Create();

    void show();

    virtual void ProcessEvents() = 0;

    void Render();

protected:

    SwapChain* context;
    Scene* scene;

};
