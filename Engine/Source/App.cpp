
#include "App.h"
#include "Platforms.h"
#include <time.h>

App* App::Instance()
{
    static PlatformApp instance;
    return &instance;
}

void App::AddWindow(WindowM* window)
{
    AddedWindows.insert(window);
}

void App::RemoveWindow(WindowM* window)
{
    RemovedWindows.insert(window);
}

void App::UpdateCollection()
{
    for (auto window : AddedWindows)
    {
        Windows.insert(window);
    }
    AddedWindows.clear();

    for (auto window : RemovedWindows)
    {
        Windows.erase(window);
    }
    RemovedWindows.clear();
}

void App::StartMainLoop()
{
    do
    {
        for (auto window : Windows)
        {
            window->ProcessEvents();
        }
        UpdateCollection();

        for (auto window : Windows)
        {
            window->Update();
            window->Render();
        }
    }
    while (Windows.size() > 0);
}
