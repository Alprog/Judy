
#pragma once

#include "AccessModifier.h"
#include "AttributeInfo.h"
#include <string>
#include <vector>
#include "TypeInfo.h"
#include "../Parser/Tokens/TokenGroup.h"

struct MemberInfo
{
    MemberInfo();

    std::vector<AttributeInfo> attributes;
    AccessModifier accessModifier;

    bool isTemplate() const;
    bool isFriend;
    std::string name;
    std::vector<std::string> templateParameters;

    bool containsAttribute(std::string name);
};
