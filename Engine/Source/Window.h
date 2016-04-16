
#pragma once

#include "Object.h"
#include "Ref.h"
#include "Node.h"
#include "Render/RenderTarget.h"
#include "Render/Renderer.h"
#include "Attributes.h"

class [[Meta]] Window : public Object
{
    friend class Meta;

public:
    static Window* Create();
    virtual ~Window();

    void show();

    virtual void ProcessEvents() = 0;

    void Update();
    void Render();

protected:
    Window();

    [[Bind]] Ref<Node> scene;
    [[Bind]] RenderTarget* renderTarget;
    [[Bind]] Renderer* renderer;

    //RenderTarget* RenderTarget1;
    //RenderTarget* RenderTarget2;
};
