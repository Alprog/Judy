
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
    void WaitForFinish();

    void OnBreak();
    void OnResume();
    void CustomNetWork();
    void OnGetMessage(Any& message);

private:
    LuaMachine* luaMachine;
    Pipe* logPipe;
    NetNode* netNode;
};
