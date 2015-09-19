
#include "FileBreakpoints.h"

FileBreakpoints::FileBreakpoints()
{
}

FileBreakpoints::FileBreakpoints(std::string fileName, std::unordered_set<int> lines)
    : fileName(fileName)
    , lines(lines)
{
}
