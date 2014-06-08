
#pragma once

class Window
{
public:
    static Window* Create();

    void show();

    virtual void SetContext() = 0;
    virtual void Swap() = 0;

};
