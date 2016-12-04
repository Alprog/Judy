
#include "Platform.h"

Platform currentPlatform()
{
#if WIN
    return Platform::Windows;
#elif LINUX
    return Platform::Linux;
#elif MAC
    return Platform::MacOS;
#else
    return Platform::Unknown;
#endif
}

std::string getPlatformName()
{
#if WIN
    return "Windows";
#elif LINUX
    return "Linux";
#elif MAC
    return "MacOS";
#else
    return "";
#endif
}
