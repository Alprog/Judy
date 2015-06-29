
#include "AttributeInfo.h"
#include "../Parser/Tokens/TokenGroup.h"

AttributeInfo::AttributeInfo(TokenGroup& tokens)
{
    name = tokens[0]->getName();
}

