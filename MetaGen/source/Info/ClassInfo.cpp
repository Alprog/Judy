
#include "ClassInfo.h"

ClassInfo::ClassInfo(TokenGroup tokens)
{
    auto arr = tokens.split(":");

    attributes = tokens.extractAttributes();
}
