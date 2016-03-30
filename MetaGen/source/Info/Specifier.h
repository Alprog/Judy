
#pragma once

#include <string>
#include "../Parser/Tokens/TokenGroup.h"

struct Specifier
{
    std::string keyword;
    bool* flag;
};

void processSpecifiers(TokenGroup& tokens, std::vector<Specifier> specifiers);
