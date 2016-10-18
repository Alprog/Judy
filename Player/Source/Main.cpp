
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

    Meta::instance()->init();

    auto luaMachine = LuaMachine::instance();

    if (debug)
    {
        auto debugger = new RemoteDebbuger(luaMachine, 0xC0DE);
        luaMachine->execute("Main.lua", true);
        delete debugger;
    }
    else
    {
        luaMachine->execute("Main.lua");
    }

}
