
#pragma once

#include "Process.h"
#include <windows.h>

class WinProcess : public Process
{
public:
    WinProcess();
    ~WinProcess();

    virtual void run(std::string path, std::string commandLine, std::string directory);
    virtual void stop();
    virtual bool isRunning();

    HANDLE handle;
    HANDLE outFileHandle;
};

using PlatformProcess = WinProcess;
