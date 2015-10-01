
#pragma once

#include "Node.h"
#include "RenderTarget.h"
#include "Renderer.h"

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
    void Render();

protected:
    WindowM();

    RenderTarget* renderTarget;
    Node* scene;
    Renderer* renderer;

    //RenderTarget* RenderTarget1;
    //RenderTarget* RenderTarget2;
};
