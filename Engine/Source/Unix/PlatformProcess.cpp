
#include "PlatformProcess.h"
#include "Utils.h"

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

UnixProcess::UnixProcess()
    : pid{0}
{
}

UnixProcess::~UnixProcess()
{
    stop();
}

void UnixProcess::run(std::string path, std::string commandLine, std::string directory)
{
    stop();

    auto argsVector = split(commandLine, " ");
    auto size = argsVector.size();
    char* argv[size + 1];
    for (auto i = 0; i < size; i++)
    {
        argv[i] = &argsVector[i][0];
    }
    argv[size] = nullptr;

    pid = fork();

    if (pid == 0) // child
    {
        chdir(directory.c_str());
        execv(path.c_str(), argv);
        _exit(1);
    }
    else // parent
    {
        if (pid < 0) // failed
        {
            pid = 0;
        }
    }
}

bool UnixProcess::isRunning()
{
    if (pid != 0)
    {
        auto result = waitpid(pid, nullptr, WNOHANG);
        if (result == 0)
        {
            return true;
        }
        else if (result == pid)
        {
            pid = 0;
        }
    }
    return false;
}

void UnixProcess::stop()
{
    if (isRunning())
    {
        if (kill(pid, SIGKILL) == 0) // send kill signal
        {
            waitpid(pid, nullptr, 0); // remove zombie
        }
    }
    pid = 0;
}
