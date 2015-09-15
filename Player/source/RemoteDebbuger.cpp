
#include "RemoteDebbuger.h"
#include "Meta/Any.h"
#include "LuaMachine/LuaMachine.h"
#include "LuaMachine/LogMessage.h"
#include "LuaMachine/Breakpoints.h"
#include "LuaMachine/DebugCommand.h"
#include "Pipe.h"
#include <regex>

using namespace std::placeholders;

RemoteDebbuger::RemoteDebbuger()
    : luaMachine{nullptr}
    , logPipe{nullptr}
    , netNode{nullptr}
{
}

void RemoteDebbuger::Start(LuaMachine* luaMachine, int port)
{
    this->luaMachine = luaMachine;
    luaMachine->breakCallback = std::bind(&RemoteDebbuger::OnBreak, this);
    luaMachine->resumeCallback = std::bind(&RemoteDebbuger::OnResume, this);

    logPipe = new Pipe(stdout);

    netNode = new NetNode();
    netNode->customWorkCallback = std::bind(&RemoteDebbuger::CustomNetWork, this);
    netNode->messageCallback = std::bind(&RemoteDebbuger::OnGetMessage, this, _1);
    netNode->Start(port);
}

void RemoteDebbuger::OnBreak()
{
    netNode->Send(luaMachine->stack);
}

void RemoteDebbuger::OnResume()
{
    netNode->Send(DebugCommand("resumed"));
}

void RemoteDebbuger::CustomNetWork()
{
    auto text = logPipe->readText();
    if (text.size() > 0)
    {
        text = std::regex_replace(text, std::regex("(\\r\\n)|(\\n)|(\\r)"), "\\n");
        text = std::regex_replace(text, std::regex("\\'"), "\\'");
        netNode->Send(LogMessage(text));
    }
}

void RemoteDebbuger::OnGetMessage(Any message)
{
    auto type = message.GetType();
    if (type == TypeMetaOf<Breakpoints>())
    {
        luaMachine->breakpoints = message.as<Breakpoints>();
        printf("get breakpoints\n");
        fflush(stdout);
    }
    else if (type == TypeMetaOf<DebugCommand>())
    {
        auto command = message.as<DebugCommand>();
        auto name = command.name;

        printf("%s \n", name.c_str());
        fflush(stdout);

        if (name == "continue")
        {
            luaMachine->Continue();
        }
        else if (name == "break")
        {
            luaMachine->Break();
        }
        else if (name == "stepInto")
        {
            luaMachine->StepInto();
        }
        else if (name == "stepOver")
        {
            luaMachine->StepOver();
        }
        else if (name == "stepOut")
        {
            luaMachine->StepOut();
        }
    }
}
