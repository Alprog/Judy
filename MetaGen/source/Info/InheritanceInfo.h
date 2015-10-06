
#pragma once

#include "AccessModifier.h"
#include <string>
#include "TypeInfo.h"

class TokenGroup;

struct InheritanceInfo
{
    InheritanceInfo(TokenGroup& tokens);

    AccessModifier accessModifier;
    TypeInfo type;
};
