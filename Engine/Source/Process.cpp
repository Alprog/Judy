
#include <Process.h>
#include <PlatformProcess.h>

Process* Process::create()
{
    return new PlatformProcess();
}
