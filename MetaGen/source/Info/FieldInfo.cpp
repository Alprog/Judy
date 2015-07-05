
#include "FieldInfo.h"

FieldInfo::FieldInfo(TokenGroup& tokens)
    : isStatic {false}
{
    attributes = tokens.extractAttributes();

}
