
#include "TypeInfo.h"
#include "../Parser/Tokens/TokenGroup.h"
#include <regex>
#include "Specifier.h"
#include "ClassInfo.h"

TypeInfo::TypeInfo()
    : isConst{false}
{
}

TypeInfo::TypeInfo(TokenGroup& tokens)
    : isConst{false}
{
    processSpecifiers(tokens,
    {
      { "const", &isConst }
    });

    tokens.makeGroups("<", ">");
    auto index = tokens.indexOf("<>");
    if (index >= 0)
    {
        auto args = tokens.extractAt(index);
        auto groups = args->cast<TokenGroup*>()->getContent().split(",");
        for (auto& group : groups)
        {
            templateArguments.push_back(group.getText());
        }
        name = tokens.getText();
    }
    else
    {
        name = tokens.getText();
    }

    refreshFullName();
}

bool TypeInfo::isTemplate() const
{
    return templateArguments.size() > 0;
}

bool TypeInfo::isDependent(ClassInfo& classInfo)
{
    for (auto& argument : templateArguments)
    {
        for (auto& parameter : classInfo.templateParameters)
        {
            if (argument == parameter)
            {
                return true;
            }
        }
    }
    return false;
}

void TypeInfo::refreshFullName()
{
    fullName = name;
    auto size = templateArguments.size();
    if (size > 0)
    {
        fullName += "<";
        for (auto i = 0; i < size; i++)
        {
            if (i > 0) { fullName += ","; };
            fullName += templateArguments[i];
        }
        fullName += ">";
    }

    fullName = std::regex_replace(fullName, std::regex(" "), "");
    fullName = std::regex_replace(fullName, std::regex(","), ", ");
}
