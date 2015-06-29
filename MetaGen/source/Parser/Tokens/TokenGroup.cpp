
#include "TokenGroup.h"

TokenGroup::TokenGroup()
{
}

TokenGroup::TokenGroup(iterator first, iterator last)
    : tokens(first, last)
{
}

TokenGroup::TokenGroup(std::string name, iterator first, iterator last)
    : name(name)
    , tokens(first, last)
{
}

std::shared_ptr<Token>& TokenGroup::operator[](int i)
{
  return tokens[i];
}

TokenGroup::iterator TokenGroup::begin()
{
    return std::begin(tokens);
}

TokenGroup::iterator TokenGroup::end()
{
    return std::end(tokens);
}

const std::string TokenGroup::getName() const
{
    return name;
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

int TokenGroup::indexOf(std::string tokenName, int startIndex) const
{
    for (auto i = startIndex; i < tokens.size(); i++)
    {
        if (tokens[i]->getName() == tokenName)
        {
            return i;
        }
    }
    return -1;
}

int TokenGroup::lastIndexOf(std::string tokenName) const
{
    auto startIndex = tokens.size() - 1;
    return lastIndexOf(tokenName, startIndex);
}

int TokenGroup::lastIndexOf(std::string tokenName, int startIndex) const
{
    for (int i = startIndex; i >= 0; i--)
    {
        if (tokens[i]->getName() == tokenName)
        {
            return i;
        }
    }
    return -1;
}

bool TokenGroup::contains(std::string tokenName) const
{
    return indexOf(tokenName) >= 0;
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

void TokenGroup::makeBracketGroups()
{
    makeGroups("(", ")");
    makeGroups("[", "]");
}

void TokenGroup::makeGroups(std::string openName, std::string closeName)
{
    while (true)
    {
        auto closeIndex = indexOf(closeName);
        if (closeIndex >= 0)
        {
            auto openIndex = lastIndexOf(openName, closeIndex - 1);
            if (openIndex >= 0)
            {
                auto first = std::begin(tokens) + openIndex;
                auto last = std::begin(tokens) + closeIndex + 1;
                auto name = openName + closeName;
                std::shared_ptr<Token> group { new TokenGroup(name, first, last) };
                tokens.erase(first, last);
                tokens.insert(std::begin(tokens) + openIndex, group);
                continue;
            }
        }
        break;
    }
}

std::vector<AttributeInfo> TokenGroup::extractAttributes()
{
    std::vector<AttributeInfo> result;

    for (auto it = std::begin(tokens); it != std::end(tokens); it++)
    {
        auto token = *it;
        if (token->getName() == "[]")
        {
            auto group = (TokenGroup*)token.get();
            if (group->tokens.size() == 3 && group->getName() == "[]")
            {
                group = (TokenGroup*)group->tokens[1].get();

                TokenGroup content(std::begin(*group) + 1, std::end(*group) - 1);
                AttributeInfo attribute(content);
                result.push_back(attribute);
                it = tokens.erase(it) - 1;
            }
        }
    }

    return result;
}
