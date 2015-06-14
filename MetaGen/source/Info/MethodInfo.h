
#pragma once

#include "MemberInfo.h"
#include <vector>
#include "ArgumentInfo.h"

class MethodInfo : public MemberInfo
{
    std::vector<ArgumentInfo> arguments;
};
