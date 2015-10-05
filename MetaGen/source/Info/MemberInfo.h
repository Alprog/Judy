
#pragma once

#include "AccessModifier.h"
#include "AttributeInfo.h"
#include <string>
#include <vector>
#include "../Parser/Tokens/TokenGroup.h"

struct MemberInfo
{
    struct Specifier
    {
        std::string keyword;
        bool* flag;
    };

    MemberInfo();

    std::vector<AttributeInfo> attributes;
    AccessModifier accessModifier;

    bool isTemplate() const;
    bool isFriend;
    std::string name;
    int templateArgumentCount;

    bool containsAttribute(std::string name);

protected:
    void processSpecifiers(TokenGroup& tokens, std::vector<Specifier> specifiers);
};
