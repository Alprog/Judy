
#include "Platform.h"

Platform currentPlatform()
{
#if WIN
    return Platform::Windows;
#elif LINUX
    return Platform::Linux;
#elif MAC
    return Platform::OSX;
#else
    return Platform::Unknown;
#endif
}

std::string getPlatformName()
{
#if WIN
    return "windows";
#elif LINUX
    return "linux";
#elif MAC
    return "osx";
#else
    return "";
#endif
}
