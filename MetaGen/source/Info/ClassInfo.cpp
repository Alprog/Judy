
#include "ClassInfo.h"

ClassInfo::ClassInfo(Tokens tokens)
{
    auto arr = tokens.split(":");

    attributes = tokens.extractAttributes();
}
