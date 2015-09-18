
#pragma once

#include <string>
#include <unordered_set>

#define __Meta__

struct __Meta__ FileBreakpoints
{
    FileBreakpoints();
    FileBreakpoints(std::string fileName, std::unordered_set<int> lines);

    std::string fileName;
    std::unordered_set<int> lines;
};
