
#include "RemotePlayer.h"
#include "Process.h"
#include "Net/NetNode.h"

#include "LuaMachine/LogMessage.h"
#include "LuaMachine/Breakpoints.h"
#include "LuaMachine/DebugCommand.h"

RemotePlayer::RemotePlayer()
    : netNode{nullptr}
    , process{nullptr}
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
        printf("%s \n", text.c_str());
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
    Continue();
}

void RemotePlayer::Break()
{
    if (netNode != nullptr)
    {
        netNode->Send(DebugCommand("break"));
    }
}

void RemotePlayer::Continue()
{
    if (netNode != nullptr)
    {
        netNode->Send(DebugCommand("continue"));
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
}
