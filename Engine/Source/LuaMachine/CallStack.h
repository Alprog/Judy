
#pragma once

#include "Containers/List.h"
#include "CallInfo.h"
#include "Attributes.h"

struct _(Meta)__ CallStack
{
    CallStack();
    _(Serialize)__ List<CallInfo> calls;
};
