
#include "TokenGroup.h"

TokenGroup::TokenGroup()
{
}

TokenGroup::TokenGroup(iterator first, iterator last)
    : tokens(first, last)
{
}

TokenGroup::~TokenGroup()
{
}

const std::string TokenGroup::getText() const
{
    std::string text = "";
    for (auto& token : tokens)
    {
        text += token->getText() + " ";
    }
    return text;
}

void TokenGroup::add(std::shared_ptr<Token> token)
{
    tokens.push_back(token);
}

bool TokenGroup::contains(std::string tokenText) const
{
    for (auto& token : tokens)
    {
        if (token->getText() == tokenText)
        {
            return true;
        }
    }
    return false;
}

std::vector<TokenGroup> TokenGroup::split(std::string delimeter)
{
    std::vector<TokenGroup> groups;

    auto start = std::begin(tokens);
    for (auto it = std::begin(tokens); it < std::end(tokens); it++)
    {
        if ((*it)->getText() == delimeter)
        {
            groups.push_back(TokenGroup(start, it));
            start = it + 1;
        }
    }
    groups.push_back(TokenGroup(start, std::end(tokens)));

    return groups;
}

TokenGroup TokenGroup::extract(std::string first, std::string last)
{
    //auto f = std::find(std::begin(tokens), std::end(tokens), first);
    //auto l = std::find(std::begin(tokens), std::end(tokens), last);
    //auto result = TokenGroup(f, l);
    //tokens.erase(f, l);
    //return result;
    return TokenGroup();
}

std::vector<std::string> TokenGroup::extractAttributes()
{
    return std::vector<std::string>();
}
