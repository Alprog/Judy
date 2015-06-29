
#pragma once

#include "Token.h"

class AtomToken : public Token
{
public:
    AtomToken(std::string text);
    const std::string getName() const override;
    const std::string getText() const override;

private:
    std::string text;
};
