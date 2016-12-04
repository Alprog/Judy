
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
    return getAttribute(name) != nullptr;
}

AttributeInfo* MemberInfo::getAttribute(std::string name)
{
    for (auto& attribute : attributes)
    {
        if (attribute.name == name)
        {
            return &attribute;
        }
    }
    return nullptr;
}
