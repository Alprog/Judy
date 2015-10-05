
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
    processTemplateTokens(tokens);

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

void ClassInfo::processTemplateTokens(TokenGroup& tokens)
{
    tokens.makeGroups("<", ">");

    auto index = tokens.indexOf("template");
    if (index >= 0 || index < tokens.size() - 1 && tokens[index + 1]->getName() == "<>")
    {
        auto groups = tokens[index + 1]->cast<TokenGroup*>()->getContent().split(",");
        for (auto& group : groups)
        {
            auto name = group.extractLast()->getName();
            templateParameters.push_back(name);
        }

        tokens.extract(index, index + 1);
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
