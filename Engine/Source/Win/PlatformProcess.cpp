
#include <PlatformProcess.h>

#include <locale>
#include <codecvt>

WinProcess::WinProcess()
    : handle{0}
    , outFileHandle{0}
{
}

WinProcess::~WinProcess()
{
    stop();
}

void WinProcess::run(std::string path, std::string commandLine, std::string directory)
{
    stop();

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    auto wpath = converter.from_bytes(path.c_str());
    auto wcommandLine = converter.from_bytes(commandLine.c_str());
    auto wdirectory = converter.from_bytes(directory.c_str());

    STARTUPINFO startupinfo;
    ZeroMemory(&startupinfo, sizeof(startupinfo));
    startupinfo.cb = sizeof(STARTUPINFO);

    PROCESS_INFORMATION processInfo;
    ZeroMemory(&(processInfo), sizeof(processInfo));

    auto result = CreateProcess(wpath.c_str(), &wcommandLine[0], 0, 0, FALSE, 0, 0, wdirectory.c_str(), &startupinfo, &processInfo);
    if (result != 0)
    {
        handle = processInfo.hProcess;
    }
}

bool WinProcess::isRunning()
{
    if (handle != 0)
    {
        DWORD exitCode;
        GetExitCodeProcess(handle, &exitCode);
        if (exitCode == STILL_ACTIVE)
        {
            return true;
        }
        else
        {
            handle = 0;
        }
    }
    if (outFileHandle != 0)
    {
        CloseHandle(outFileHandle);
    }
    return false;
}

void WinProcess::stop()
{
    if (isRunning())
    {
        TerminateProcess(handle, 1);
    }
    handle = 0;
}
