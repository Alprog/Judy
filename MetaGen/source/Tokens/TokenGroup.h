
#pragma once

#include "Token.h"
#include <vector>
#include <string>
#include <memory>

class TokenGroup : Token
{
private:
    using iterator = std::vector<std::shared_ptr<Token>>::iterator;

public:
    TokenGroup();
    TokenGroup(iterator first, iterator last);

    const std::string getText() const override;

    void add(std::shared_ptr<Token> token);
    bool contains(std::string tokenText) const;
    std::vector<TokenGroup> split(std::string delimeter);

    TokenGroup extract(std::string first, std::string last);
    std::vector<std::string> extractAttributes();

private:
    std::vector<std::shared_ptr<Token>> tokens;
};
