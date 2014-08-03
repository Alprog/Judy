
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

private:
    void UpdateCollection();

    std::set<Window*> Windows;
    std::set<Window*> AddedWindows;
    std::set<Window*> RemovedWindows;
};
