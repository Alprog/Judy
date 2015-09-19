
#pragma once
#include <string>

#define __Meta__

struct __Meta__ CallInfo
{
    friend class Meta;

private:
    CallInfo();

public:
    CallInfo(std::string name, std::string source, int line, int startLine, int endLine);

    std::string name;
    std::string source;
    int line;
    int startLine;
    int endLine;
};
