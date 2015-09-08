
#include "RemotePlayer.h"

#include <windows.h>

RemotePlayer::RemotePlayer()
    : netNode{nullptr}
{
}

void RemotePlayer::Start()
{
    auto path = L"D:\\Judy\\Build\\Win\\Player\\Player.exe";
    auto currentDirectory = L"D:\\Judy\\Build\\Win\\Player";

    STARTUPINFO sti;
    ZeroMemory(&sti, sizeof(STARTUPINFO));
    sti.cb = sizeof(STARTUPINFO);
    PROCESS_INFORMATION pi;
    CreateProcess(path, 0, 0, 0, FALSE, 0, 0, currentDirectory, &sti, &pi);
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
