
#pragma once

#include <string>
#include "Attributes.h"

struct [[Meta]] DebugCommand
{
    DebugCommand();
    DebugCommand(std::string name);

    [[Serialize]] std::string name;
};
