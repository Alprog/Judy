
#pragma once

#include "Process.h"
#include <windows.h>

class WinProcess : public Process
{
public:
    WinProcess();
    ~WinProcess();

    virtual void Run(std::string path, std::string commandLine, std::string directory);
    virtual void Stop();
    virtual bool IsRunning();

    HANDLE handle;
};
