
#include "AtomToken.h"

AtomToken::AtomToken(std::string text)
    : text(text)
{
}

const std::string AtomToken::getName() const
{
    return text;
}

const std::string AtomToken::getText() const
{
    return text;
}
