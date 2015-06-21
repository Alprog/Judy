
#include "Tokens.h"

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
