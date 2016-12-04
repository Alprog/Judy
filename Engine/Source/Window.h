
#pragma once

#include "Object.h"
#include "Ref.h"
#include "Node.h"
#include "Render/RenderTarget.h"
#include "Render/IRenderer.h"
#include "Attributes.h"

class [[Meta]] Window : public Object
{
    friend class Meta;

public:
    static Window* create();
    virtual ~Window();

    void show();

    virtual void processEvents() = 0;

    void update(float delta);
    void render();

    virtual void setRenderer(IRenderer* renderer) = 0;
    virtual void switchRenderType() = 0;

protected:
    Window();

    [[Bind]] Ref<Node> scene;
    [[Bind]] RenderTarget* renderTarget;
    [[Bind]] IRenderer* renderer;

    //RenderTarget* RenderTarget1;
    //RenderTarget* RenderTarget2;
};
