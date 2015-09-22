
#include "UnixProcess.h"

UnixProcess::UnixProcess()
//    : handle{0}
{
}

UnixProcess::~UnixProcess()
{
    Stop();
}

void UnixProcess::Run(std::string path, std::string commandLine, std::string directory)
{
    Stop();


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
    //handle = 0;
}
