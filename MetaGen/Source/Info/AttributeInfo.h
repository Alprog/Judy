
#pragma once

#include <string>

class TokenGroup;

struct AttributeInfo
{
public:
    AttributeInfo(TokenGroup& tokens);
    std::string name;
    std::string value;
};
