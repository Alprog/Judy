
#include "RemotePlayer.h"

#include <windows.h>
#include <cstdio>
#include <thread>

RemotePlayer::RemotePlayer()
    : netNode{nullptr}
{
}

void RemotePlayer::Start()
{
    LPWSTR path = L"D:\\Judy\\Build\\Win\\Player\\Player.exe";
    LPWSTR commandLine = L"player.exe -debug";
    LPWSTR currentDirectory = L"D:\\Judy\\Player";

    STARTUPINFO sti;
    ZeroMemory(&sti, sizeof(sti));
    sti.cb = sizeof(STARTUPINFO);

    PROCESS_INFORMATION pi;
    ZeroMemory(&(pi), sizeof(pi));

    int result = CreateProcess(path, commandLine, 0, 0, FALSE, 0, 0, currentDirectory, &sti, &pi);

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
