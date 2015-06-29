
#include "TypeInfo.h"

TypeInfo::TypeInfo()
{
}

TypeInfo::TypeInfo(TokenGroup tokens)
{
    name = tokens.getText();
}
