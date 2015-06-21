
#pragma once

#include "TypeInfo.h"
#include "../Tokens.h"

struct ArgumentInfo
{
    ArgumentInfo(Tokens tokens);

    TypeInfo typeInfo;
    std::string name;
};
