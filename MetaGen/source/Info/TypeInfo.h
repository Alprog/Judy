
#pragma once

#include <string>
#include "../Parser/Tokens/TokenGroup.h"

struct TypeInfo
{
    TypeInfo();
    TypeInfo(TokenGroup tokens);

    std::string name;
};
