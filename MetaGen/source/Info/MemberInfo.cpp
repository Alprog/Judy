
#include "MemberInfo.h"

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
