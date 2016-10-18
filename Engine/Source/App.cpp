
#include "App.h"
#include <PlatformApp.h>

#include <time.h>
#include "Input/InputSystem.h"

App* App::Instance()
{
    static PlatformApp instance;
    return &instance;
}

App::App()
{
    Retain();
}

void App::AddWindow(Window* window)
{
    addedWindows.insert(window);
}

void App::RemoveWindow(Window* window)
{
    removedWindows.insert(window);
}

void App::UpdateCollection()
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

void App::StartMainLoop()
{
    do
    {
        for (auto window : windows)
        {
            window->ProcessEvents();
        }
        UpdateCollection();

        InputSystem::Instance()->UpdateState();

        for (auto window : windows)
        {
            window->Update();
            window->Render();
        }
    }
    while (windows.size() > 0);
}
