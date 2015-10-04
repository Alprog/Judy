
#pragma once
#include <string>

#define __Meta__
#define __Serialize__

struct __Meta__ CallInfo
{
    friend class Meta;

private:
    CallInfo();

public:
    CallInfo(std::string name, std::string source, int line, int startLine, int endLine);

    __Serialize__  std::string name, source;
    __Serialize__  int line, startLine, endLine;
};
