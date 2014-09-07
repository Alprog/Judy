
#pragma once

#include "Node.h"
#include "RenderTarget.h"

class Window
{
public:
    static Window* Create();

    void show();

    virtual void ProcessEvents() = 0;

    void Render();

protected:
    Window();

protected:

    Node* scene;
    RenderTarget* RenderTarget1;
    RenderTarget* RenderTarget2;
};
