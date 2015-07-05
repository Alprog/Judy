
#include "FieldInfo.h"

FieldInfo::FieldInfo(TokenGroup& tokens)
    : isStatic {false}
{
    attributes = tokens.extractAttributes();

    printf("%s\n", tokens.getText().c_str());
}
