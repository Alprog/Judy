
#include "LuaMachine/LuaMachine.h"
#include "RemoteDebbuger.h"

#include "App.h"

int main(int argc, char *argv[])
{
    auto debug = false;
    for (int i = 0; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "-d" || arg == "-debug")
        {
            debug = true;
        }

    }

    auto luaMachine = LuaMachine::Instance();

    if (debug)
    {
        auto debugger = RemoteDebbuger::Instance();
        debugger->Start(luaMachine, 2730);
        luaMachine->Do("Main.lua", true);
        debugger->WaitForFinish();
    }
    else
    {
        luaMachine->Do("Main.lua");
    }

}
