
#pragma once

#include "AccessModifier.h"
#include <string>
class TokenGroup;

struct InheritanceInfo
{
    InheritanceInfo(TokenGroup& tokens);

    AccessModifier accessModifier;
    std::string name;
};
