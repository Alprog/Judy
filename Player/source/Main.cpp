
#include "LuaMachine/LuaMachine.h"
#include <thread>
#include <chrono>

#include "Socket.h"

void serverTask()
{
    auto server = new Socket();
    server->Host(2730);
    const char* str = server->Read();
    printf("%s\n", str);
}

void clientTask()
{
    auto client = new Socket();
    while (!client->Connect("127.0.0.1", 2730)) {}
    client->Send("Albukerke!");
}

int main(int argc, char *argv[])
{
    std::thread serverThread(serverTask);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread clientThread(clientTask);

    clientThread.join();
    serverThread.join();

    printf("finish\n");
    fflush(stdout);

    //LuaMachine::Instance()->Start("main.lua");
}

/*template <typename Type>
void SerialzeToTable(lua_State* L, Type object)
{
    auto serializer = new Serializer(L);
    serializer->Serialize(object);

    auto a = serializer->DeserializeUnknown();
    lua_pop(L, 1);
    serializer->Serialize(a);

    lua_getglobal(L, "Test");
    lua_insert(L, 1);
    lua_pcall(L, 1, LUA_MULTRET, 0);
}*/

/*int main(int argc, char *argv[])
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    LuaBinder(L).Bind(Meta::Instance());
    fflush(stdout);


    if (luaL_dofile(L, "main.lua"))
    {
        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }

    TestStruct testStruct { 1.0, 2, "fff", SubStruct() };
    SerialzeToTable(L, testStruct);

    lua_close(L);
}*/
