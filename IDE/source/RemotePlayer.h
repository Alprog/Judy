
#pragma once

#include "Singleton.h"
#include <unordered_set>
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
    void SetBreakpoints(std::string source, std::unordered_set<int> lines);

private:
    void CustomNetWork();
    void OnGetMessage(Any message);

public:
    CallStack stack;

private:
    Process* process;
    NetNode* netNode;
    Breakpoints breakpoints;
    bool isPaused;
};
