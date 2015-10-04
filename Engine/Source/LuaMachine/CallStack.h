
#pragma once

#include <vector>
#include "CallInfo.h"

#define __Meta__
#define __Serialize__

struct __Meta__ CallStack
{
    CallStack();
    __Serialize__ std::vector<CallInfo> calls;
};
