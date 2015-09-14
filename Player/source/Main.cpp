
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
        RemoteDebbuger::Instance()->Start(luaMachine, 2730);
    }

    luaMachine->Start("main.lua", debug);
}
