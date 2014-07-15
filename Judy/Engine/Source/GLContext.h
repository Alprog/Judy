
#pragma once

class GLContext
{
public:
    virtual void MakeCurrent() = 0;
    virtual void Swap() = 0;
};
