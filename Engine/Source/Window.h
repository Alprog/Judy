
#pragma once

#include "Scene.h"
#include "RenderTarget.h"

class Window
{
public:
    static Window* Create();

    void show();

    virtual void ProcessEvents() = 0;

    void Render();

protected:

    Scene* scene;
    RenderTarget* RenderTarget1;
    RenderTarget* RenderTarget2;
};
