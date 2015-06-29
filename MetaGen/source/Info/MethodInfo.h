
#pragma once

#include "MemberInfo.h"
#include <vector>
#include "ArgumentInfo.h"
class TokenGroup;

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
