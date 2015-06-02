
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
    serializer->Serialize(any);
}
