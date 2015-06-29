
#pragma once

#include "TypeInfo.h"
#include "../Parser/Tokens/TokenGroup.h"

struct ArgumentInfo
{
    ArgumentInfo(TokenGroup tokens);

    TypeInfo typeInfo;
    std::string name;
};
