
#include "App.h"
#include "Platforms.h"

using namespace Judy;

App* App::Instance()
{
    static PlatformApp instance;
    return &instance;
}
