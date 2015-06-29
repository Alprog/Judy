
#pragma once

#include "TypeInfo.h"
class TokenGroup;

struct ArgumentInfo
{
    ArgumentInfo(TokenGroup& tokens);

    TypeInfo typeInfo;
    std::string name;
};
