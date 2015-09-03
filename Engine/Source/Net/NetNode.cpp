
#include "NetNode.h"

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

NetNode::NetNode()
{
    L = luaL_newstate();
    luaL_openlibs(L);
    lua_getglobal(L, "package");
    lua_pushstring(L, "?.lua");
    lua_setfield(L, -2, "path");
    luaL_dofile(L, "Serializer.lua");
    serializer = new Serializer(L);
}

NetNode::~NetNode()
{
    serializer = nullptr;
    lua_close(L);
    L = nullptr;
    //socket->Close();
}

void NetNode::Send(Any& any)
{
    lua_getglobal(L, "TableToString");
    serializer->Serialize(any);
    lua_pcall(L, 1, 1, 0);
    std::string text = lua_tostring(L, -1);
    printf("%s \n", text.c_str());
}
