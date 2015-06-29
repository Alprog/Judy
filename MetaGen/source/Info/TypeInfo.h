
#pragma once

#include <string>
#include "../Tokens/TokenGroup.h"

struct TypeInfo
{
    TypeInfo();
    TypeInfo(TokenGroup tokens);

    std::string name;
};
