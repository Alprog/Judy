
#pragma once

#include <string>
#include "Attributes.h"

struct _(Meta)__ DebugCommand
{
    DebugCommand();
    DebugCommand(std::string name);

    _(Serialize)__ std::string name;
};
