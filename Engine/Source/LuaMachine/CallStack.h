
#pragma once

#include "Containers/List.h"
#include "CallInfo.h"
#include "Attributes.h"

struct [[Meta]] CallStack
{
    CallStack();
    [[Serialize]] List<CallInfo> calls;
};
