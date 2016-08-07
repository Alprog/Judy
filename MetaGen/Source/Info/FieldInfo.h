
#pragma once

#include "MemberInfo.h"
#include "TypeInfo.h"
#include "../Parser/Tokens/TokenGroup.h"

struct FieldInfo : MemberInfo
{
    FieldInfo(TokenGroup& tokens);

    bool isStatic;
    TypeInfo type;
};
