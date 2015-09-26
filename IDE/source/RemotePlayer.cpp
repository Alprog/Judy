
#include "RemotePlayer.h"
#include "Process.h"
#include "Net/NetNode.h"

#include "LuaMachine/LogMessage.h"
#include "LuaMachine/Breakpoints.h"
#include "LuaMachine/Filebreakpoints.h"
#include "LuaMachine/DebugCommand.h"
#include "LuaMachine/CallStack.h"
#include "IDE.h"

using namespace std::placeholders;

RemotePlayer::RemotePlayer()
    : netNode{nullptr}
    , process{nullptr}
    , isPaused{false}
{
    connect(this, SIGNAL(StateChanged()), IDE::Instance(), SLOT(OnPlayerStateChanged()));
}

RemotePlayer::~RemotePlayer()
{
    Stop();
}

void RemotePlayer::Run()
{
    Stop();

    auto& settings = IDE::Instance()->settings;
    auto path = settings.playerPath;
    auto directory = settings.projectPath;
    auto commandLine = "player -debug";

    printf("%s %s %s\n", path.c_str(), directory.c_str(), commandLine);
    fflush(stdout);

    process = Process::Create();
    process->Run(path, commandLine, directory);

    if (!process->IsRunning())
    {
        delete process;
        process = nullptr;
        return;
    }

    netNode = new NetNode();
    netNode->customWorkCallback = std::bind(&RemotePlayer::CustomNetWork, this);
    netNode->messageCallback = std::bind(&RemotePlayer::OnGetMessage, this, _1);
    netNode->Connect("127.0.0.1", 2730);

    for (auto& pair : breakpoints.getMap())
    {
        netNode->Send(FileBreakpoints(pair.first, pair.second));
    }
    netNode->Send(DebugCommand("continue"));
}

bool RemotePlayer::IsRunning()
{
    if (netNode != nullptr)
    {
        if (netNode->GetState() != NetNode::State::Disconnected)
        {
            return true;
        }
        else
        {
            Stop();
        }
    }
    return false;
}

bool RemotePlayer::IsConnected()
{
    return netNode != nullptr && netNode->GetState() == NetNode::State::Connected;
}

bool RemotePlayer::IsPaused()
{
    return isPaused;
}

void RemotePlayer::SendCommand(std::string name)
{
    if (IsConnected())
    {
        netNode->Send(DebugCommand(name));
    }
}

CallInfo* RemotePlayer::GetActiveCall()
{
    if (stack.calls.size() > 0)
    {
        return &stack.calls[0];
    }
    else
    {
        return nullptr;
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
    stack.calls.clear();
    StateChanged();
}

void RemotePlayer::CustomNetWork()
{
}

void RemotePlayer::OnGetMessage(Any& message)
{
    if (message.GetType() == TypeMetaOf<LogMessage>())
    {
        auto text = message.as<LogMessage>().text;
        printf("%s", text.c_str());
    }
    else if (message.GetType() == TypeMetaOf<CallStack>())
    {
        isPaused = true;
        stack = message.as<CallStack>();
        StateChanged();
    }
    else if (message.GetType() == TypeMetaOf<DebugCommand>())
    {
        stack.calls.clear();
        isPaused = false;
        StateChanged();
    }
    else
    {
        printf("new message \n");
    }
}

std::unordered_set<int> RemotePlayer::GetBreakpoints(std::string source)
{
    return breakpoints.Get(source);
}

void RemotePlayer::SetBreakpoints(std::string source, std::unordered_set<int> lines)
{
    bool changed = breakpoints.Set(source, lines);
    if (changed && IsConnected())
    {
        netNode->Send(FileBreakpoints(source, lines));
    }
}
