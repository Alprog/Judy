
#include "Tokens.h"

Tokens::Tokens()
{
}

Tokens::Tokens(std::vector<std::string>::iterator first, std::vector<std::string>::iterator last)
    : items(first, last)
{
}

void Tokens::add(std::string token)
{
    items.push_back(token);
}

std::string Tokens::getText() const
{
    std::string text = "";
    for (auto& token : items)
    {
        text += token + " ";
    }
    return text;
}

bool Tokens::contains(std::string token) const
{
    for (auto& item : items)
    {
        if (item == token)
        {
            return true;
        }
    }
    return false;
}

std::vector<Tokens> Tokens::split(std::string delimeter)
{
    std::vector<Tokens> groups;

    auto start = std::begin(items);
    for (auto it = std::begin(items); it < std::end(items); it++)
    {
        if (*it == delimeter)
        {
            groups.push_back(Tokens(start, it));
            start = it + 1;
        }
    }
    groups.push_back(Tokens(start, std::end(items)));

    return groups;
}

Tokens Tokens::extract(std::string first, std::string last)
{
    auto f = std::find(std::begin(items), std::end(items), first);
    auto l = std::find(std::begin(items), std::end(items), last);
    auto result = Tokens(f, l);
    items.erase(f, l);
    return result;
}

std::vector<std::string> Tokens::extractAttributes()
{
    return std::vector<std::string>();
}
