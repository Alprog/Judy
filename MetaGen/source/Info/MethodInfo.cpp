
#include "MethodInfo.h"

MethodInfo::MethodInfo(Tokens tokens)
{
    auto argumentsTokens = tokens.extract("(", ")");
    for (auto& argumentTokens : argumentsTokens.split(","))
    {
        arguments.push_back(ArgumentInfo(argumentTokens));
    }
}
