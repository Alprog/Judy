
#pragma once

#include "Object.h"
#include "Ref.h"
#include "Node.h"
#include "RenderTarget.h"
#include "Renderer.h"
#include "Attributes.h"

class [[Meta]] WindowM : public Object
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

    [[Bind]] Ref<Node> scene;
    [[Bind]] RenderTarget* renderTarget;
    [[Bind]] Renderer* renderer;

    //RenderTarget* RenderTarget1;
    //RenderTarget* RenderTarget2;
};
