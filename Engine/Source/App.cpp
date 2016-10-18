
#include "App.h"
#include <PlatformApp.h>

#include <time.h>
#include "Input/InputSystem.h"

App* App::instance()
{
    static PlatformApp instance;
    return &instance;
}

App::App()
{
    retain();
}

void App::addWindow(Window* window)
{
    addedWindows.insert(window);
}

void App::removeWindow(Window* window)
{
    removedWindows.insert(window);
}

void App::updateCollection()
{
    for (auto window : addedWindows)
    {
        windows.insert(window);
    }
    addedWindows.clear();

    for (auto window : removedWindows)
    {
        windows.erase(window);
        delete window;
    }
    removedWindows.clear();
}

void App::startMainLoop()
{
    do
    {
        for (auto window : windows)
        {
            window->processEvents();
        }
        updateCollection();

        InputSystem::instance()->updateState();

        for (auto window : windows)
        {
            window->update();
            window->render();
        }
    }
    while (windows.size() > 0);
}
