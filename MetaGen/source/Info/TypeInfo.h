
#pragma once

#include <string>
class TokenGroup;

struct TypeInfo
{
    TypeInfo();
    TypeInfo(TokenGroup& tokens);
    std::string name;
};
