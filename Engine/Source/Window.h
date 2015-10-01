
#pragma once

#include "Node.h"
#include "RenderTarget.h"

#define __Meta__

class __Meta__ WindowM
{
    friend class Meta;

public:
    static WindowM* Create();
    virtual ~WindowM();

    void show();

    virtual void ProcessEvents() = 0;

    void Update();
    virtual void Render();
    Node* scene;

protected:
    WindowM();
    RenderTarget* RenderTarget1;
    RenderTarget* RenderTarget2;
};
