
#pragma once

#include <string>

#define __Meta__
#define __Serialize__

struct __Meta__ DebugCommand
{
    DebugCommand();
    DebugCommand(std::string name);

    __Serialize__ std::string name;
};
