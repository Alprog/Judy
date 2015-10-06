
#include "MemberInfo.h"

MemberInfo::MemberInfo()
    : isFriend(false)
{
}

bool MemberInfo::isTemplate() const
{
    return templateParameters.size() > 0;
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
