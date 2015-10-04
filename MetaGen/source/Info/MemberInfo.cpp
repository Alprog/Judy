
#include "MemberInfo.h"

MemberInfo::MemberInfo()
    : isFriend(false)
    , isTemplate{false}
{
}

bool MemberInfo::containsAttribute(std::string name)
{
    for (auto& attribute : attributes)
    {
        if (attribute.name == name)
        {
            return true;
        }
    }
    return false;
}

void MemberInfo::processSpecifiers(TokenGroup& tokens, std::vector<Specifier> specifiers)
{
    for (auto i = 0; i < tokens.size(); i++)
    {
        auto name = tokens[i]->getName();
        for (auto& s : specifiers)
        {
            if (name == s.keyword)
            {
                *s.flag = true;
                tokens.extractAt(i--);
                break;
            }
        }
    }
}
