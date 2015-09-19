
#pragma once

#include <string>

#define __Meta__

struct __Meta__ DebugCommand
{
    DebugCommand();
    DebugCommand(std::string name);

    std::string name;
};
