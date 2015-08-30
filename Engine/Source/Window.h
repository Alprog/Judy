
#pragma once

#include "Node.h"
#include "RenderTarget.h"

class Window
{
    friend class Meta;
    friend class TypeMeta<Window>;

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
