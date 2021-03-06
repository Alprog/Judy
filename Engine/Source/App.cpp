
#include "App.h"
#include <PlatformApp.h>

#include <time.h>
#include "Input/InputSystem.h"
#include <chrono>

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
    auto prev = std::chrono::system_clock::now();

    do
    {
        auto cur = std::chrono::system_clock::now();
        float delta = static_cast<std::chrono::duration<float>>(cur - prev).count();
        prev = cur;

        for (auto window : windows)
        {
            window->processEvents();
        }
        updateCollection();

        InputSystem::getInstance()->updateState();

        for (auto window : windows)
        {
            window->update(delta);
            window->render();
        }
    }
    while (windows.size() > 0);
}
