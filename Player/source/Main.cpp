
#include "LuaMachine/LuaMachine.h"
#include <thread>
#include <chrono>

#include "Net/NetNode.h"
#include "Net/Socket.h"

int main(int argc, char *argv[])
{
    auto server = new NetNode();
    server->listen(2730);

    auto client = new NetNode();
    client->connect("127.0.0.1", 2730);

    while (!server->isConnnected())
    {

    }
    while (!client->isConnnected())
    {

    }

    printf("connected \n");
    fflush(stdout);

//    auto m = Meta::Instance();

//    auto node = new NetNode();

//    Any a = SubStruct();
//    //node->Send(a);

}

//void serverTask()
//{
//    auto server = new Socket();
//    server->Listen(2730);
//    server->Accept();
//    const char* str = server->Receive();
//    printf("%s\n", str);
//}

//void clientTask()
//{
//    auto client = new Socket();
//    while (!client->Connect("127.0.0.1", 2730)) {}
//    client->Send("Albukerke!");
//}

//int main(int argc, char *argv[])
//{
////    auto server = new Socket();
////    server->SetBlockingMode(false);
////    server->Listen(2730);
////    server->Accept();

//    std::thread serverThread(serverTask);
//    std::this_thread::sleep_for(std::chrono::milliseconds(100));
//    std::thread clientThread(clientTask);

//    clientThread.join();
//    serverThread.join();

//    printf("finish\n");
//    fflush(stdout);

//    //LuaMachine::Instance()->Start("main.lua");
//}

//extern "C"
//{
//    #include "lua.h"
//    #include "lualib.h"
//    #include "lauxlib.h"
//}

//#include "Meta/Meta.h"
//#include "Meta/Binder.h"
//#include "Meta/Serializer.h"
//#include "App.h"
//#include <iostream>

//template <typename Type>
//void SerialzeToTable(lua_State* L, Type object)
//{
//    auto serializer = new Serializer(L);
//    serializer->Serialize(object);

//    auto a = serializer->DeserializeUnknown();
//    lua_pop(L, 1);
//    serializer->Serialize(a);

//    lua_getglobal(L, "Test");
//    lua_insert(L, 2);
//    lua_pcall(L, 1, 0, 0);
//}


//int main(int argc, char *argv[])
//{
//    lua_State* L = luaL_newstate();
//    luaL_openlibs(L);
//    lua_getglobal(L, "package");
//    lua_pushstring(L, "?.lua");
//    lua_setfield(L, -2, "path");

//    LuaBinder(L).Bind(Meta::Instance());
//    fflush(stdout);


//    if (luaL_dofile(L, "Main.lua"))
//    {
//        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
//        std::cerr << lua_tostring(L, -1) << std::endl;
//        lua_pop(L, 1);
//    }

//    TestStruct testStruct { 1.0, 2, "fff", SubStruct() };
//    SerialzeToTable(L, testStruct);

//    fflush(stdout);

//    lua_close(L);
//}
