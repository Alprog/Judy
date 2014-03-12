
#include "App.h"
#include "Windows.h"

App* App::Instance()
{
    static App instance;
    return &instance;
}

App::App()
    : WindowCount(0)
{
}

void App::StartMainLoop()
{
    MSG msg;
    while(WindowCount > 0)
    {
        PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

