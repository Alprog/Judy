
#include "AtomToken.h"

AtomToken::AtomToken(std::string text)
    : text(text)
{
}

const std::string AtomToken::getText() const
{
    return text;
}
