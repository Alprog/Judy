
#pragma once

#include <vector>
#include "CallInfo.h"

#define __Meta__

struct __Meta__ CallStack
{
    CallStack();
    std::vector<CallInfo> calls;
};
