
#pragma once

#include "Socket.h"
#include "Meta/Any.h"
#include "Meta/Serializer.h"

class NetNode
{
public:
    NetNode();
    ~NetNode();

    void Send(Any& any);

private:
    lua_State* L;
    Serializer* serializer;
    Socket socket;
};
