
#pragma once

#include "Containers/List.h"
#include "CallInfo.h"

#define __Meta__
#define __Serialize__

struct __Meta__ CallStack
{
    CallStack();
    __Serialize__ List<CallInfo> calls;
};
