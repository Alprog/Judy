
#include "App.h"
#include "Platforms.h"

App* App::Instance()
{
    static PlatformApp instance;
    return &instance;
}

void App::AddWindow(Window* window)
{
    Windows.insert(window);
}

void App::RemoveWindow(Window* window)
{
    Windows.erase(window);
}

void App::StartMainLoop()
{
    while(Windows.size() > 0)
    {
        for(auto window : Windows)
        {
            window->ProcessEvents();
        }
    }
}
