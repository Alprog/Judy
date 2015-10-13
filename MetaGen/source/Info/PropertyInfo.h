
#pragma once

#include "MemberInfo.h"
#include "MethodInfo.h"
#include "../Parser/Tokens/TokenGroup.h"

struct PropertyInfo : public MemberInfo
{
    PropertyInfo(TokenGroup& tokens);

    void addMethod(TokenGroup& tokens);

    bool hasGetter() const;
    bool hasSetter() const;

    MethodInfo getter;
    MethodInfo setter;
};
