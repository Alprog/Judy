
#pragma once

#include "Meta/Any.h"
#include "LuaMachine/LuaMachine.h"
#include "Pipe.h"
#include "Net/NetNode.h"

class RemoteDebbuger
{
public:
    RemoteDebbuger(LuaMachine* luaMachine, int port);
    ~RemoteDebbuger();

private:
    void waitForFinish();

    void onBreak();
    void onResume();
    void customNetWork();
    void onGetMessage(Any& message);

private:
    LuaMachine* luaMachine;
    Pipe* logPipe;
    NetNode* netNode;
};
