
#pragma once

#include "Process.h"
#include <unistd.h>

class UnixProcess : public Process
{
public:
    UnixProcess();
    ~UnixProcess();

    virtual void Run(std::string path, std::string commandLine, std::string directory);
    virtual void Stop();
    virtual bool IsRunning();

    pid_t pid;
};
