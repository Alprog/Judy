
#pragma once

#include <string>
#include <vector>
#include "InheritanceInfo.h"
#include "MethodInfo.h"

struct ClassInfo
{
    std::string name;
    std::vector<InheritanceInfo> inheritances;

    std::vector<MethodInfo> constructors;
    std::vector<MethodInfo> methods;

};
