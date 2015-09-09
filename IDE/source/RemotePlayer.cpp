
#include "RemotePlayer.h"
#include "Net/NetNode.h"
#include "LuaMachine/LogMessage.h"
#include "LuaMachine/Breakpoints.h"
#include "LuaMachine/DebugCommand.h"

#include <windows.h>
#include <cstdio>
#include <thread>

RemotePlayer::RemotePlayer()
    : netNode{nullptr}
{
}

void CustomWork()
{
}

void MessageCallback(Any message)
{
    if (message.GetType() == TypeMetaOf<LogMessage>())
    {
        auto text = message.as<LogMessage>().text;
        printf("%s \n", text.c_str());
    }
}

void RemotePlayer::Start()
{
    LPWSTR path = (LPWSTR)L"D:\\Judy\\Build\\Win\\Player\\Player.exe";
    LPWSTR commandLine = (LPWSTR)L"player.exe -debug";
    LPWSTR currentDirectory = (LPWSTR)L"D:\\Judy\\Player";

    STARTUPINFO sti;
    ZeroMemory(&sti, sizeof(sti));
    sti.cb = sizeof(STARTUPINFO);

    PROCESS_INFORMATION pi;
    ZeroMemory(&(pi), sizeof(pi));

    CreateProcess(path, commandLine, 0, 0, FALSE, 0, 0, currentDirectory, &sti, &pi);

    netNode = new NetNode();
    netNode->customWork = CustomWork;
    netNode->messageCallback = MessageCallback;
    netNode->Connect("127.0.0.1", 2730);

    Any breakpoints = Breakpoints();
    netNode->Send(breakpoints);

    Any command = DebugCommand("continue");
    netNode->Send(command);
}

void RemotePlayer::Break()
{

}

void RemotePlayer::Continue()
{

}

void RemotePlayer::Stop()
{

}
