
#pragma once
#include <string>

class Process
{
public:
    static Process* create();

    virtual ~Process() = default;

    virtual void run(std::string path, std::string commandLine, std::string directory) = 0;
    virtual void stop() = 0;
    virtual bool isRunning() = 0;
};
