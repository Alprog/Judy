
#include "FileBreakpoints.h"

FileBreakpoints::FileBreakpoints()
{
}

FileBreakpoints::FileBreakpoints(std::string fileName, Set<int> lines)
    : fileName(fileName)
    , lines(lines)
{
}
