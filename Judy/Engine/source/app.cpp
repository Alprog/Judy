
#include "App.h"
#include "Platforms.h"

App* App::Instance()
{
    static WinApp instance;
    return &instance;
}



