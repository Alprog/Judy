
#pragma once
#include <string>
#include "Attributes.h"

struct [[Meta]] CallInfo
{
    friend class Meta;

public:
    CallInfo();
    CallInfo(std::string name, std::string source, int line, int startLine, int endLine);

    [[Serialize]]  std::string name, source;
    [[Serialize]]  int line, startLine, endLine;
};
