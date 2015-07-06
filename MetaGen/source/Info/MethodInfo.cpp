
#include "MethodInfo.h"
#include "../Parser/Tokens/TokenGroup.h"

#include <iostream>

MethodInfo::MethodInfo(TokenGroup& tokens)
    : isStatic {false}
    , isVirtual {false}
    , isOperator {false}
    , isConst {false}
    , isOverride {false}
{
    attributes = tokens.extractAttributes();

    processArguments(tokens);
    processSpecifiers(tokens);

    name = tokens.extractLast()->getName();
    returnType = TypeInfo(tokens);
}

void MethodInfo::processArguments(TokenGroup& tokens)
{
    auto index = tokens.indexOf("()");
    if (index >= 0)
    {
        auto& parentheses = tokens[index];
        auto content = parentheses->cast<TokenGroup*>()->getContent();
        if (content.size() > 0)
        {
            for (auto& argumentTokens : content.split(","))
            {
                arguments.push_back(ArgumentInfo(argumentTokens));
            }
        }
    }
}

void MethodInfo::processSpecifiers(TokenGroup& tokens)
{
    auto arr = tokens.split("()");

    MemberInfo::processSpecifiers(arr[0],
    {
      { "friend", &isFriend },
      { "static", &isStatic },
      { "virtual", &isVirtual },
      { "operator", &isOperator }
    });

    if (arr.size() > 1)
    {
        MemberInfo::processSpecifiers(arr[1],
        {
            { "override", &isOverride },
            { "const", &isConst }
        });
    }

    tokens = arr[0];
}
