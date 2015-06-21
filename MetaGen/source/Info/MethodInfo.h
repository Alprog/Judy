
#pragma once

#include "MemberInfo.h"
#include <vector>
#include "ArgumentInfo.h"

class MethodInfo : public MemberInfo
{
    bool isStatic;
    bool isVirtual;

    TypeInfo returnType;
    std::vector<ArgumentInfo> arguments;

    bool isConst;
    bool isOverride;
};
