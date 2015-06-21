
#pragma once

#include "MemberInfo.h"
#include "TypeInfo.h"

struct FieldInfo : MemberInfo
{
    bool isStatic;
    TypeInfo type;
};
