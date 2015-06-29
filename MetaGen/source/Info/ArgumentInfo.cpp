
#include "ArgumentInfo.h"

#include <vector>
#include "../Parser/Tokens/TokenGroup.h"

ArgumentInfo::ArgumentInfo(TokenGroup& tokens)
{
    auto arr = tokens.split("=");
}
