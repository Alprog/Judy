
#pragma once

#include "MemberInfo.h"
#include <vector>
#include "ArgumentInfo.h"

class TokenGroup;

struct MethodInfo : public MemberInfo
{
    MethodInfo();
    MethodInfo(TokenGroup& tokens);

    bool isStatic;
    bool isVirtual;
    bool isOperator;
    bool isInline;

    TypeInfo returnType;
    std::vector<ArgumentInfo> arguments;

    bool isConst;
    bool isOverride;
    bool isPure;

private:
    void processOperator(TokenGroup& tokens);
    void processArguments(TokenGroup& tokens);
    void processSpecifiers(TokenGroup& tokens);
};
