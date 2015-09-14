
#include "RemotePlayer.h"
#include "Process.h"
#include "Net/NetNode.h"

#include "LuaMachine/LogMessage.h"
#include "LuaMachine/Breakpoints.h"
#include "LuaMachine/DebugCommand.h"
#include "LuaMachine/CallStack.h"

RemotePlayer::RemotePlayer()
    : netNode{nullptr}
    , process{nullptr}
    , isPaused{false}
{
}

RemotePlayer::~RemotePlayer()
{
    Stop();
}

void CustomWork()
{
}

void MessageCallback(Any message)
{
    if (message.GetType() == TypeMetaOf<LogMessage>())
    {
        auto text = message.as<LogMessage>().text;
        printf("%s", text.c_str());
    }
    else if (message.GetType() == TypeMetaOf<CallStack>())
    {
        RemotePlayer::Instance()->isPaused = true;
        printf("breakpoint\n");
    }
    else
    {
        printf("new message \n");
    }
}

void RemotePlayer::Run()
{
    Stop();

    auto path = "D:\\Judy\\Build\\Win\\Player\\Player.exe";
    auto commandLine = "player.exe -debug";
    auto directory = "D:\\Judy\\Player";

    process = Process::Create();
    process->Run(path, commandLine, directory);

    if (!process->IsRunning())
    {
        delete process;
        return;
    }

    netNode = new NetNode();
    netNode->customWork = CustomWork;
    netNode->messageCallback = MessageCallback;
    netNode->Connect("127.0.0.1", 2730);

    netNode->Send(Breakpoints());
    netNode->Send(DebugCommand("continue"));
}

bool RemotePlayer::IsRunning()
{
    return process != nullptr && process->IsRunning();
}

bool RemotePlayer::IsConnected()
{
    return netNode != nullptr && netNode->GetState() == NetNode::State::Connected;
}

bool RemotePlayer::IsPaused()
{
    return isPaused;
}

void RemotePlayer::Pause()
{
    if (IsConnected())
    {
        netNode->Send(DebugCommand("break"));
    }
}

void RemotePlayer::Continue()
{
    if (IsConnected())
    {
        netNode->Send(DebugCommand("continue"));
        isPaused = false;
    }
}

void RemotePlayer::Stop()
{
    if (netNode != nullptr)
    {
        delete netNode;
        netNode = nullptr;
    }
    if (process != nullptr)
    {
        delete process;
        process = nullptr;
    }
    isPaused = false;
}
