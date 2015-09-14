
#pragma once

#include "Meta/Any.h"
#include "LuaMachine/LuaMachine.h"
#include "Pipe.h"
#include "Net/NetNode.h"

class RemoteDebbuger : public Singleton<RemoteDebbuger>
{
    friend class Singleton<RemoteDebbuger>;

    RemoteDebbuger();

public:
    void Start(LuaMachine* luaMachine, int port);

private:
    void OnBreak();
    void CustomNetWork();
    void OnGetMessage(Any message);

private:
    LuaMachine* luaMachine;
    Pipe* logPipe;
    NetNode* netNode;
};
