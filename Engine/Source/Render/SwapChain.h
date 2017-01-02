
#pragma once

#include <RenderTarget.h>

class SwapChain
{
public:
    SwapChain(RenderTarget* renderTarget);

    virtual void refreshSize() = 0;

protected:
    RenderTarget* renderTarget;
};
