
#include "RemotePlayer.h"
#include "Process.h"
#include "Net/NetNode.h"

#include "LuaMachine/LogMessage.h"
#include "LuaMachine/Breakpoints.h"
#include "LuaMachine/FileBreakpoints.h"
#include "LuaMachine/DebugCommand.h"
#include "LuaMachine/CallStack.h"
#include "IDE.h"

#define NO_STDIO_REDIRECT

using namespace std::placeholders;

RemotePlayer::RemotePlayer()
    : netNode{nullptr}
    , process{nullptr}
    , isPausedFlag{false}
{
    connect(this, SIGNAL(stateChanged()), IDE::getInstance(), SLOT(onPlayerStateChanged()));
}

RemotePlayer::~RemotePlayer()
{
    stop();
}

void RemotePlayer::run()
{
    stop();

    auto& settings = IDE::getInstance()->settings;
    auto path = settings.playerPath;
    auto directory = settings.projectPath;
    auto commandLine = "player -debug";

    fprintf(stdout, "%s %s %s\n", path.c_str(), directory.c_str(), commandLine);
    fflush(stdout);

    process = Process::create();
    process->run(path, commandLine, directory);
    if (!process->isRunning())
    {
        delete process;
        process = nullptr;
        return;
    }

    netNode = new NetNode();
    netNode->customWorkCallback = std::bind(&RemotePlayer::customNetWork, this);
    netNode->messageCallback = std::bind(&RemotePlayer::onGetMessage, this, _1);
    netNode->connect("127.0.0.1", 0xC0DE);

    for (auto& pair : breakpoints.getMap())
    {
        netNode->send(FileBreakpoints(pair.first, pair.second));
    }
    netNode->send(DebugCommand("resume"));
}

bool RemotePlayer::isRunning()
{
    if (netNode != nullptr)
    {
        if (netNode->getState() != NetNode::State::Disconnected)
        {
            return true;
        }
        else
        {
            stop();
        }
    }
    return false;
}

bool RemotePlayer::isConnected()
{
    return netNode != nullptr && netNode->getState() == NetNode::State::Connected;
}

bool RemotePlayer::isPaused()
{
    return isPausedFlag;
}

void RemotePlayer::sendCommand(std::string name)
{
    if (isConnected())
    {
        netNode->send(DebugCommand(name));
    }
}

CallInfo* RemotePlayer::getActiveCall()
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

void RemotePlayer::stop()
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
    isPausedFlag = false;
    stack.calls.clear();
    stateChanged();
}

void RemotePlayer::customNetWork()
{
}

void RemotePlayer::onGetMessage(Any& message)
{
    if (message.getType() == typeMetaOf<LogMessage>())
    {
        auto text = message.as<LogMessage>().text;
        printf("%s", text.c_str());
        fflush(stdout);
    }
    else if (message.getType() == typeMetaOf<CallStack>())
    {
        isPausedFlag = true;
        stack = message.as<CallStack>();
        stateChanged();
    }
    else if (message.getType() == typeMetaOf<DebugCommand>())
    {
        stack.calls.clear();
        isPausedFlag = false;
        stateChanged();
    }
    else
    {
        printf("new message \n");
    }
}

Set<int> RemotePlayer::getBreakpoints(std::string source)
{
    return breakpoints.getLines(source);
}

void RemotePlayer::setBreakpoints(std::string source, Set<int> lines)
{
    bool changed = breakpoints.setLines(source, lines);
    if (changed && isConnected())
    {
        netNode->send(FileBreakpoints(source, lines));
    }
}
