
#include "RemoteDebbuger.h"
#include "Meta/Any.h"
#include "LuaMachine/LuaMachine.h"
#include "LuaMachine/LogMessage.h"
#include "LuaMachine/FileBreakpoints.h"
#include "LuaMachine/DebugCommand.h"
#include "Pipe.h"
#include <regex>
#include <functional>

using namespace std::placeholders;

RemoteDebbuger::RemoteDebbuger(LuaMachine* luaMachine, int port)
    : luaMachine{nullptr}
    , logPipe{nullptr}
    , netNode{nullptr}
{
    this->luaMachine = luaMachine;
    luaMachine->breakCallback = std::bind(&RemoteDebbuger::onBreak, this);
    luaMachine->resumeCallback = std::bind(&RemoteDebbuger::onResume, this);

    logPipe = new Pipe(stdout);

    netNode = new NetNode();
    netNode->customWorkCallback = std::bind(&RemoteDebbuger::customNetWork, this);
    netNode->messageCallback = std::bind(&RemoteDebbuger::onGetMessage, this, _1);
    netNode->start(port);
}

RemoteDebbuger::~RemoteDebbuger()
{
    waitForFinish();

    if (netNode != nullptr)
    {
        delete netNode;
        netNode = nullptr;
    }
    if (logPipe != nullptr)
    {
        delete logPipe;
        logPipe = nullptr;
    }
}

void RemoteDebbuger::waitForFinish()
{
    fflush(stdout);
    customNetWork();
    while (netNode->isConnected() && netNode->hasOutput())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void RemoteDebbuger::onBreak()
{
    netNode->send(luaMachine->stack);
}

void RemoteDebbuger::onResume()
{
    netNode->send(DebugCommand("resumed"));
}

void RemoteDebbuger::customNetWork()
{
    auto text = logPipe->readText();
    if (text.size() > 0)
    {
        text = std::regex_replace(text, std::regex("(\\r\\n)|(\\n)|(\\r)"), "\\n");
        text = std::regex_replace(text, std::regex("\\'"), "\\'");
        netNode->send(LogMessage(text));
    }
}

void RemoteDebbuger::onGetMessage(Any& message)
{
    auto type = message.getType();
    if (type == typeMetaOf<DebugCommand>())
    {
        auto command = message.as<DebugCommand>();
        auto name = command.name;
        if (name == "resume")
        {
            luaMachine->resume();
        }
        else if (name == "pause")
        {
            luaMachine->pause();
        }
        else if (name == "stepInto")
        {
            luaMachine->stepInto();
        }
        else if (name == "stepOver")
        {
            luaMachine->stepOver();
        }
        else if (name == "stepOut")
        {
            luaMachine->stepOut();
        }
        else if (name == "win")
        {
            luaMachine->breakpoints.setCaseSensitive(false);
        }
    }
    else if (type == typeMetaOf<FileBreakpoints>())
    {
        auto fileBreakpoints = message.as<FileBreakpoints>();
        luaMachine->breakpoints.setLines(fileBreakpoints.fileName, fileBreakpoints.lines);

        printf("breaks get\n");
        fflush(stdout);
    }
}
