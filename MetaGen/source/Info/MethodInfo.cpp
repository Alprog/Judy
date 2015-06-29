
#include "MethodInfo.h"

MethodInfo::MethodInfo(TokenGroup tokens)
{
    auto argumentsTokens = tokens.extract("(", ")");
    for (auto& argumentTokens : argumentsTokens.split(","))
    {
        arguments.push_back(ArgumentInfo(argumentTokens));
    }
}
