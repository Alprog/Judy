
#pragma once

#include <string>
#include <unordered_set>

#define __Meta__
#define __Serialize__

struct __Meta__ FileBreakpoints
{
    FileBreakpoints();
    FileBreakpoints(std::string fileName, std::unordered_set<int> lines);

    __Serialize__ std::string fileName;
    __Serialize__ std::unordered_set<int> lines;
};
