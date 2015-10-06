
#pragma once

#include <string>
#include "Containers/Set.h"

#define __Meta__
#define __Serialize__

struct __Meta__ FileBreakpoints
{
    FileBreakpoints();
    FileBreakpoints(std::string fileName, Set<int> lines);

    __Serialize__ std::string fileName;
    __Serialize__ Set<int> lines;
};
