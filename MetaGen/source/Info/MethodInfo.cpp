
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
    processSpecifiers(tokens);
    processArguments(tokens);

    name = tokens.extractLast()->getName();
    returnType = TypeInfo(tokens);
}

void MethodInfo::processSpecifiers(TokenGroup& tokens)
{
    struct pair
    {
        std::string keyword;
        bool* flag;
    };

    std::vector<pair> pairs
    {
        { "friend", &isFriend },
        { "static", &isStatic },
        { "virtual", &isVirtual },
        { "operator", &isOperator },
        { "override", &isOverride },
        { "const", &isConst },
    };

    auto visitParenthesis = false;
    for (auto i = 0; i < tokens.size(); i++)
    {
        auto name = tokens[i]->getName();

        if (name == "()")
        {
            visitParenthesis = true;
            continue;
        }

        for (pair& p : pairs)
        {
            if (name == p.keyword)
            {
                if (name == "const" && !visitParenthesis)
                {
                    continue;
                }
                *p.flag = true;
                tokens.extractAt(i--);
                break;
            }
        }
    }
}

void MethodInfo::processArguments(TokenGroup& tokens)
{
    auto index = tokens.indexOf("()");
    if (index >= 0)
    {
        auto token = tokens.extractAt(index);
        auto content = token->cast<TokenGroup*>()->getContent();
        if (content.size() > 0)
        {
            for (auto& argumentTokens : content.split(","))
            {
                arguments.push_back(ArgumentInfo(argumentTokens));
            }
        }
    }
}
