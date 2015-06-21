
#include "TypeInfo.h"

TypeInfo::TypeInfo()
{
}

TypeInfo::TypeInfo(Tokens tokens)
{
    name = tokens.getText();
}
