
#pragma once
#include <string>

enum class Platform
{
    Windows,
    Linux,
    OSX,
    Unknown
};

Platform currentPlatform();
std::string getPlatformName();

#if WIN
    #define PLATFORM_TYPE(x) Win ## x
#elif LINUX
    #define PLATFORM_TYPE(x) Linux ## x
#elif MAC
    #define PLATFORM_TYPE(x) Mac ## x
#endif

#define PLATFORM_FORWARD_DECLARE(x)         \
    class PLATFORM_TYPE(x);                 \
    using Platform ## x = PLATFORM_TYPE(x);
