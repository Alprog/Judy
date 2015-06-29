
#pragma once

#include "MemberInfo.h"
#include <vector>
#include "ArgumentInfo.h"
#include "../Parser/Tokens/TokenGroup.h"

class MethodInfo : public MemberInfo
{
    MethodInfo(TokenGroup tokens);

    bool isStatic;
    bool isVirtual;
    bool isOperator;

    TypeInfo returnType;
    std::vector<ArgumentInfo> arguments;

    bool isConst;
    bool isOverride;
};
