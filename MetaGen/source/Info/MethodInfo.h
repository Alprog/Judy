
#pragma once

#include "MemberInfo.h"
#include <vector>
#include "ArgumentInfo.h"

class MethodInfo : public MemberInfo
{
    bool isVirtual;
    bool isConst;
    bool isOverride;
    std::vector<ArgumentInfo> arguments;
};
