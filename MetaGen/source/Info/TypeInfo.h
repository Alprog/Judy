
#pragma once

#include <string>
#include "../Tokens.h"

struct TypeInfo
{
    TypeInfo();
    TypeInfo(Tokens tokens);

    std::string name;
};
