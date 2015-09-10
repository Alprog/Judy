
#include "Process.h"
#include "Platforms.h"

Process* Process::Create()
{
    return new PlatformProcess();
}
