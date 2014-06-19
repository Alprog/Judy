
#pragma once

class Context
{
public:
    virtual void MakeCurrent() = 0;
    virtual void Swap() = 0;
};

