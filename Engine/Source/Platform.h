
#pragma once
#include <string>

enum class Platform
{
    Windows,
    Linux,
    OSX,
    Unknown
};

Platform CurrentPlatform();
std::string GetPlatformName();
