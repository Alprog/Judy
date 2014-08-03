
#pragma once

#include <set>
#include "Window.h"

class App
{
public:
    static App* Instance();

    void StartMainLoop();

    void AddWindow(Window* window);
    void RemoveWindow(Window* window);

protected:
    std::set<Window*> Windows;
};
