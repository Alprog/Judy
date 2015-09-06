
#include "LuaMachine/LuaMachine.h"
#include "Net/NetNode.h"

#include "App.h"


NetNode* server = nullptr;

int main(int argc, char *argv[])
{
    LuaMachine::Instance()->Start("main.lua");

    Window* window = Window::Create();

    App::Instance()->AddWindow(window);

    App::Instance()->StartMainLoop();
}
