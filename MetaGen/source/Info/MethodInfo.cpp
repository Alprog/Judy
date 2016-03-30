
#include "MethodInfo.h"
#include "../Parser/Tokens/TokenGroup.h"

#include <iostream>
#include "Specifier.h"

MethodInfo::MethodInfo()
{
}

MethodInfo::MethodInfo(TokenGroup& tokens)
    : isStatic {false}
    , isVirtual {false}
    , isOperator {false}
    , isConst {false}
    , isOverride {false}
    , isPure {false}
    , isInline {false}
{
    attributes = tokens.extractAttributes();

    processOperator(tokens);
    processArguments(tokens);
    processSpecifiers(tokens);

    if (!isOperator)
    {
        name = tokens.extractLast()->getName();
    }
    returnType = TypeInfo(tokens);
}

void MethodInfo::processOperator(TokenGroup& tokens)
{
    auto index = tokens.indexOf("operator");
    if (index >= 0)
    {
        isOperator = true;

        auto lastIndex = tokens.indexOf("()", index);
        if (lastIndex >= 0)
        {
            auto group = tokens.extract(index, lastIndex);
            name = group.getText();
        }
    }
}

void MethodInfo::processArguments(TokenGroup& tokens)
{
    auto index = tokens.indexOf("()");
    if (index >= 0)
    {
        auto& parentheses = tokens[index];
        auto content = parentheses->cast<TokenGroup*>()->getContent();
        content.makeTemplateGroups();
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

    ::processSpecifiers(arr[0],
    {
      { "friend", &isFriend },
      { "static", &isStatic },
      { "virtual", &isVirtual },
      { "inline", &isInline }
    });

    if (arr.size() > 1)
    {
        ::processSpecifiers(arr[1],
        {
            { "override", &isOverride },
            { "const", &isConst },
            { "0", &isPure }
        });
    }

    tokens = arr[0];
}
