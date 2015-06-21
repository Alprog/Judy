
#pragma once

#include "AccessModifier.h"
#include "AttributeInfo.h"
#include <string>
#include <vector>

struct MemberInfo
{
    std::vector<std::string> attributes;
    AccessModifier accessModifier;
    std::string name;
};
