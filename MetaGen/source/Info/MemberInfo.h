
#pragma once

#include "AccessModifier.h"
#include "AttributeInfo.h"
#include <string>
#include <vector>

struct MemberInfo
{
    MemberInfo();

    std::vector<AttributeInfo> attributes;
    AccessModifier accessModifier;

    bool isFriend;
    std::string name;

    bool containsAttribute(std::string name);
};
