
#pragma once

#include "AccessModifier.h"
#include "TypeInfo.h"
#include <string>

struct MemberInfo
{
    bool isStatic;
    AccessModifier accessModifier;
    TypeInfo type;
    std::string name;
};
