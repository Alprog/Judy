
#pragma once

#include "AccessModifier.h"
#include "AttributeInfo.h"
#include <string>
#include <vector>

struct MemberInfo
{
    std::vector<AttributeInfo> attributes;
    AccessModifier accessModifier;
    std::string name;

    bool containsAttribute(std::string name);
};
