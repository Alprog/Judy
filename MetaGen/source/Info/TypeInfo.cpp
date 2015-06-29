
#include "TypeInfo.h"
#include "../Parser/Tokens/TokenGroup.h"

TypeInfo::TypeInfo()
{
}

TypeInfo::TypeInfo(TokenGroup& tokens)
{
    name = tokens.getText();
}
