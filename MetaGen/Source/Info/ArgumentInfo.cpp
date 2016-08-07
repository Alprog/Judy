
#include "ArgumentInfo.h"

#include <vector>
#include "../Parser/Tokens/TokenGroup.h"

ArgumentInfo::ArgumentInfo(TokenGroup& tokens)
{
    auto v = tokens.split("=");
    proccessMainTokens(v[0]);
    if (v.size() > 1)
    {
        defaultValue = v[1].getText();
    }
}

void ArgumentInfo::proccessMainTokens(TokenGroup& tokens)
{
    auto token = tokens.extractLast();
    name = token->getName();
    type = TypeInfo(tokens);
}
