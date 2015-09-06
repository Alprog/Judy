
#pragma once

#include "Node.h"
#include "RenderTarget.h"

#define __Meta__

class __Meta__ Window
{
    friend class Meta;

public:
    static Window* Create();

    void show();

    virtual void ProcessEvents() = 0;

    void Render();
    Node* scene;

protected:
    Window();    
    RenderTarget* RenderTarget1;
    RenderTarget* RenderTarget2;
};
