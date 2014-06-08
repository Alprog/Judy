
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
        /*std::set<Window*>::iterator it;
        for (it = Windows.begin(); it != Windows.end(); ++it)
        {
            Window* w = *it;
            w->ProcessEvents();
        }*/

        /*for(auto w : Windows)
        {
            w->ProcessEvents();
        }*/
    }
}
