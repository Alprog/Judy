
#pragma once

#include <string>
#include "Containers/Set.h"
#include "Attributes.h"

struct _(Meta)__ FileBreakpoints
{
    FileBreakpoints();
    FileBreakpoints(std::string fileName, Set<int> lines);

    _(Serialize)__ std::string fileName;
    _(Serialize)__ Set<int> lines;
};
