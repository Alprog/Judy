
#include "CallInfo.h"

CallInfo::CallInfo()
{
}

CallInfo::CallInfo(std::string name, std::string source, int line, int startLine, int endLine)
    : name(name)
    , source(source)
    , line{line}
    , startLine{startLine}
    , endLine{endLine}
{
}
