
#pragma once

#include <string>
#include "Containers/Set.h"
#include "Attributes.h"

struct [[Meta]] FileBreakpoints
{
    FileBreakpoints();
    FileBreakpoints(std::string fileName, Set<int> lines);

    [[Serialize]] std::string fileName;
    [[Serialize]] Set<int> lines;
};
