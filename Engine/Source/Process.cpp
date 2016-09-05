
#include <Process.h>
#include <PlatformProcess.h>

Process* Process::Create()
{
    return new PlatformProcess();
}
