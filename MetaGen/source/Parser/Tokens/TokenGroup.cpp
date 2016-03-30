
#include "TokenGroup.h"
#include "AtomToken.h"

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

std::vector<Token>::size_type TokenGroup::size()
{
    return tokens.size();
}

const std::string TokenGroup::getName() const
{
    return name;
}

const std::string TokenGroup::getText() const
{
    bool first = true;
    std::string text = "";
    for (auto& token : tokens)
    {
        if (!first)
        {
            text += " ";
        }
        text += token->getText();
        first = false;
    }
    return text;
}

void TokenGroup::decay(std::string name)
{
    auto index = indexOf(name);
    while (index >= 0)
    {
        extractAt(index);
        for (auto i = 0; i < name.size(); i++)
        {
            auto text = name.substr(i, 1);
            std::shared_ptr<Token> token { new AtomToken(text) };
            insert(index, token);
        }
        index = indexOf(name);
    }
}

void TokenGroup::insert(int index, std::shared_ptr<Token> token)
{
    tokens.insert(std::begin(tokens) + index, token);
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
    return lastIndexOf(tokenName, (int)startIndex);
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

TokenGroup TokenGroup::extract(int first, int last)
{
    auto f = std::begin(tokens) + first;
    auto l = std::begin(tokens) + last;
    auto group = TokenGroup(f, l);
    tokens.erase(f, l);
    return group;
}

std::shared_ptr<Token> TokenGroup::extractAt(int index)
{
    auto token = tokens[index];
    tokens.erase(std::begin(tokens) + index);
    return token;
}

std::shared_ptr<Token> TokenGroup::extractLast()
{
    return extractAt(tokens.size() - 1);
}

std::vector<TokenGroup> TokenGroup::split(std::string delimeter)
{
    std::vector<TokenGroup> groups;

    auto start = std::begin(tokens);
    for (auto it = std::begin(tokens); it < std::end(tokens); it++)
    {
        if ((*it)->getName() == delimeter)
        {
            groups.push_back(TokenGroup(start, it));
            start = it + 1;
        }
    }
    if (start != std::end(tokens))
    {
        groups.push_back(TokenGroup(start, std::end(tokens)));
    }
    return groups;
}

void TokenGroup::makeBracketGroups()
{
    makeGroups("(", ")");
    makeGroups("[", "]");
}

void TokenGroup::makeTemplateGroups()
{
    decay("<<");
    decay(">>");
    makeGroups("<", ">");
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

std::vector<TokenGroup> TokenGroup::splitDeclararion()
{
    makeTemplateGroups();

    auto array = split(",");
    if (array.size() > 1)
    {
        auto begin = std::begin(array[0]);
        auto end = std::end(array[0]);

        iterator it;
        for (it = begin; it < end - 1; it++)
        {
            auto name = (*it)->getName();
            if (name == "*" || name == "&")
            {
                break;
            }
        }

        for (int i = 1; i < array.size(); i++)
        {
            auto& group = array[i];
            group.tokens.insert(std::begin(group), begin, it);
        }

    }
    return array;
}

std::vector<AttributeInfo> TokenGroup::extractAttributes()
{
    std::vector<AttributeInfo> result;

    auto it = std::begin(tokens);
    while (it != std::end(tokens))
    {
        auto token = *it;
        if (token->getName() == "[]")
        {
            auto group = token->cast<TokenGroup*>();
            if (group->size() == 3 && group->tokens[1]->getName() == "[]")
            {
                group = group->tokens[1]->cast<TokenGroup*>();
                auto content = group->getContent();
                auto attributes = content.split(",");
                for (auto& attributeTokens : attributes)
                {
                    AttributeInfo attribute(attributeTokens);
                    result.push_back(attribute);
                }
                it = tokens.erase(it);
                continue;
            }
        }
        it++;
    }

    return result;
}

TokenGroup TokenGroup::getContent()
{
    return TokenGroup(std::begin(tokens) + 1, std::end(tokens) - 1);
}
