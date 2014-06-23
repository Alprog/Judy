
#pragma once

class SwapChain
{
public:
    virtual void MakeCurrent() = 0;
    virtual void Swap() = 0;
};

