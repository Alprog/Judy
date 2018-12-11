
#pragma once

#include "Process.h"
#include <unistd.h>

class UnixProcess : public Process
{
public:
    UnixProcess();
    ~UnixProcess();

    virtual void run(std::string path, std::string commandLine, std::string directory);
    virtual void stop();
    virtual bool isRunning();

    pid_t pid;
};

using PlatformProcess = UnixProcess;
