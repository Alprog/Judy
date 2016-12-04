
#include "AttributeInfo.h"
#include "../Parser/Tokens/TokenGroup.h"

AttributeInfo::AttributeInfo(TokenGroup& tokens)
{
    name = tokens[0]->getName();

    auto index = tokens.indexOf("()");
    if (index >= 0)
    {
        auto content = tokens[index]->cast<TokenGroup*>()->getContent();
        value = content.getText();
    }
}

