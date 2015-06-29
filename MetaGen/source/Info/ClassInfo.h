
#pragma once

#include <string>
#include <vector>
#include "InheritanceInfo.h"
#include "MethodInfo.h"
#include "FieldInfo.h"
#include "MemberInfo.h"
#include "../Tokens/TokenGroup.h"

struct ClassInfo : MemberInfo
{
    ClassInfo(TokenGroup tokens);

    bool isFinal;
    std::vector<InheritanceInfo> inheritances;

    std::vector<MethodInfo> constructors;
    std::vector<MethodInfo> methods;
    std::vector<FieldInfo> fields;
};
