
#pragma once

#include <string>

struct Token
{
public:
    virtual const std::string getText() const = 0;
};
