
#include "ClassInfo.h"
#include "../Parser/Tokens/TokenGroup.h"

ClassInfo::ClassInfo(TokenGroup& tokens)
    : classType{ClassType::Class}
    , isFinal{false}
{
    auto arr = tokens.split(":");
    processMainTokens(arr[0]);
    if (arr.size() > 1)
    {
        processInheritanceTokens(arr[1]);
    }
}

AccessModifier ClassInfo::getDefaultAccessModifier()
{
    if (classType == ClassType::Class)
    {
        return AccessModifier::Private;
    }
    else
    {
        return AccessModifier::Public;
    }
}

bool ClassInfo::isAbstract()
{
    for (auto& method : methods)
    {
        if (method.isVirtual && method.isPure)
        {
            return true;
        }
    }
    return false;
}

void ClassInfo::processMainTokens(TokenGroup& tokens)
{
    attributes = tokens.extractAttributes();

    tokens.makeGroups("<", ">");
    if (tokens.size() >= 2)
    {
        if (tokens[0]->getName() == "template" && tokens[1]->getName() == "<>")
        {
            auto args = tokens[1]->cast<TokenGroup*>()->split(",");
            templateArgumentCount = args.size();
        }
    }

    std::string keyword;
    for (auto& token : tokens)
    {
        auto tokenName = token->getName();
        if (tokenName == "final")
        {
            isFinal = true;
        }
        else if (tokenName == "class")
        {
            classType = ClassType::Class;
            keyword = tokenName;
        }
        else if (tokenName == "struct")
        {
            classType = ClassType::Struct;
            keyword = tokenName;
        }
        else if (tokenName == "union")
        {
            classType = ClassType::Union;
            keyword = tokenName;
        }
    }

    if (keyword != "")
    {
        auto nameIndex = tokens.indexOf(keyword) + 1;
        name = tokens[nameIndex]->getName();
    }
}

void ClassInfo::processInheritanceTokens(TokenGroup& tokens)
{
    for (auto& group : tokens.split(","))
    {
        auto info = InheritanceInfo(group);
        inheritances.push_back(info);
    }
}
