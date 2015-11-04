
#pragma once

#include "Node.h"
#include "RenderTarget.h"
#include "Renderer.h"
#include "Attributes.h"

class _(Meta)__ WindowM
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

    _(Bind)__ RenderTarget* renderTarget;
    _(Bind)__ Node* scene;
    _(Bind)__ Renderer* renderer;

    //RenderTarget* RenderTarget1;
    //RenderTarget* RenderTarget2;
};
