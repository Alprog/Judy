
#include "RemoteDebbuger.h"
#include "Meta/Any.h"
#include "LuaMachine/LuaMachine.h"
#include "LuaMachine/LogMessage.h"
#include "LuaMachine/Breakpoints.h"
#include "LuaMachine/DebugCommand.h"
#include "Pipe.h"
#include <regex>

NetNode* RemoteDebbuger::netNode = nullptr;
Pipe* logPipe = nullptr;

void CustomWork()
{
    auto text = logPipe->readText();
    if (text.size() > 0)
    {
        text = std::regex_replace(text, std::regex("(\\r\\n)|(\\n)|(\\r)"), "\\n");
        text = std::regex_replace(text, std::regex("\\'"), "\\'");
        Any message = LogMessage {text};
        RemoteDebbuger::netNode->Send(message);
    }
}

void MessageCallback(Any message)
{
    auto type = message.GetType();
    if (type == TypeMetaOf<Breakpoints>())
    {
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
            LuaMachine::Instance()->Continue();
        }
        else if (name == "break")
        {
            LuaMachine::Instance()->Break();
        }
    }
}

void BreakCallback(LuaMachine* luaMachine)
{
    RemoteDebbuger::netNode->Send(luaMachine->stack);
}

void RemoteDebbuger::Start(int port)
{
    logPipe = new Pipe(stdout);
    LuaMachine::Instance()->breakCallback = BreakCallback;
    netNode = new NetNode();
    netNode->customWork = CustomWork;
    netNode->messageCallback = MessageCallback;
    netNode->Start(port);
}
