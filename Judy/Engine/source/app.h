
#pragma once

#include "Window.h"
#include "Renderer.h"

class App
{
public:
    static App* Instance();

    int WindowCount;
    void StartMainLoop();

    Renderer* Renderer;

private:
    App();

};
