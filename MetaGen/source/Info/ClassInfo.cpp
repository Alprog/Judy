
#include "ClassInfo.h"
#include "../Parser/Tokens/TokenGroup.h"

ClassInfo::ClassInfo(TokenGroup& tokens)
{
    auto arr = tokens.split(":");
    processMainTokens(arr[0]);
    if (arr.size() > 1)
    {
        processInheritanceTokens(arr[1]);
    }
}

void ClassInfo::processMainTokens(TokenGroup& tokens)
{
    attributes = tokens.extractAttributes();

//    for (auto& token : tokens)
//    {
//        printf("%s\n", token->getName().c_str());
//    }
}

void ClassInfo::processInheritanceTokens(TokenGroup& tokens)
{
    for (auto& group : tokens.split(","))
    {
        auto info = InheritanceInfo(group);
        inheritances.push_back(info);
    }
}
