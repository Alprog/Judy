
#include "FieldInfo.h"

FieldInfo::FieldInfo(TokenGroup& tokens)
    : isStatic {false}
{
    attributes = tokens.extractAttributes();

    name = tokens.extractLast()->getName();
    type = TypeInfo(tokens);
}