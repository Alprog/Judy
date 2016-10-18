
#pragma once

class GLContext
{
public:
    virtual void makeCurrent() = 0;
    virtual void swap() = 0;
};
