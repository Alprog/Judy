
#include "LuaMachine/LuaMachine.h"
#include "RemoteDebbuger.h"

#include "App.h"
#include "Meta/Meta.h"

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

    Meta::Instance()->Init();

    auto luaMachine = LuaMachine::Instance();

    if (debug)
    {
        auto debugger = new RemoteDebbuger(luaMachine, 0xC0DE);
        luaMachine->Do("Main.lua", true);
        delete debugger;
    }
    else
    {
        luaMachine->Do("Main.lua");
    }
}