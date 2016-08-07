
#pragma once

#include <string>
#include "Meta/ClassDefiner.h"

struct Settings
{
    std::string playerPath;
    std::string projectPath;

    static void InitMeta();
};
