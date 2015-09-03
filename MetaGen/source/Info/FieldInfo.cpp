
#include "FieldInfo.h"

FieldInfo::FieldInfo(TokenGroup& tokens)
    : isStatic {false}
{
    attributes = tokens.extractAttributes();

    processSpecifiers(tokens,
    {
      { "static", &isStatic },
    });

    name = tokens.extractLast()->getName();
    type = TypeInfo(tokens);
}
