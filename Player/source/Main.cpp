
#include "LuaMachine/LuaMachine.h"
#include "Net/NetNode.h"

#include "App.h"


NetNode* server = nullptr;

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

    if (debug)
    {

    }

    LuaMachine::Instance()->Start("main.lua");
}
