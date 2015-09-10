
#pragma once
#include <string>

class Process
{
public:
    static Process* Create();

    virtual ~Process() = default;

    virtual void Run(std::string path, std::string commandLine, std::string directory) = 0;
    virtual void Stop() = 0;
    virtual bool IsRunning() = 0;
};
