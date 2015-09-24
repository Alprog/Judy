
#include "UnixProcess.h"
#include "Utils.h"

#include <unistd.h>

UnixProcess::UnixProcess()
    : pid{0}
{
}

UnixProcess::~UnixProcess()
{
    Stop();
}

void UnixProcess::Run(std::string path, std::string commandLine, std::string directory)
{
    Stop();



    auto argsVector = Split(commandLine, ' ');

    auto size = argsVector.size();
    auto argv = new char*[size + 1];

    for (auto i = 0; i < size; i++)
    {
        argv[i] = argsVector[i].c_str();
    }
    argv[size] = nullptr;

    pid = fork();
    if (pid == 0)
    {
        //exec()
    }
}

bool UnixProcess::IsRunning()
{

    return false;
}

void UnixProcess::Stop()
{
    if (IsRunning())
    {

    }
    pid = 0;
}
