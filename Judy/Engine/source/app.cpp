
#include "App.h"
#include "Platforms.h"

App* App::Instance()
{
    static PlatformApp instance;
    return &instance;
}



