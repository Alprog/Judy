
#pragma once
#include <string>
#include "Attributes.h"

struct _(Meta)__ CallInfo
{
    friend class Meta;

public:
    CallInfo();
    CallInfo(std::string name, std::string source, int line, int startLine, int endLine);

    _(Serialize)__  std::string name, source;
    _(Serialize)__  int line, startLine, endLine;
};
