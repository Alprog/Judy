
#include "GenericInfo.h"

GenericInfo::GenericInfo()
    : classInfo{nullptr}
{
}

GenericInfo::GenericInfo(ClassInfo* classInfo)
    : classInfo{classInfo}
{
}
