
#pragma once

#include "Singleton.h"
#include "LuaMachine/Breakpoints.h"
#include "LuaMachine/CallStack.h"
#include "Meta/Any.h"

class NetNode;
class Process;

class RemotePlayer : public Singleton<RemotePlayer>
{
    friend class Singleton<RemotePlayer>;

protected:
    RemotePlayer();
    ~RemotePlayer();

public:
    void Run();
    void Stop();

    bool IsRunning();
    bool IsConnected();
    bool IsPaused();

    void SendCommand(std::string name);
    CallInfo* GetActiveCall();

private:

    void CustomNetWork();
    void OnGetMessage(Any message);

public:
    CallStack stack;
    Breakpoints breakpoints;

private:
    Process* process;
    NetNode* netNode;
    bool isPaused;
};
