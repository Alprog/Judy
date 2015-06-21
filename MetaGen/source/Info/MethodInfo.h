
#pragma once

#include "MemberInfo.h"
#include <vector>
#include "ArgumentInfo.h"
#include "../Tokens.h"

class MethodInfo : public MemberInfo
{
    MethodInfo(Tokens tokens);

    bool isStatic;
    bool isVirtual;
    bool isOperator;

    TypeInfo returnType;
    std::vector<ArgumentInfo> arguments;

    bool isConst;
    bool isOverride;
};
