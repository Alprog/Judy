
#pragma once

#include <QObject>
#include "Singleton.h"
#include "Containers/Set.h"
#include "LuaMachine/Breakpoints.h"
#include "LuaMachine/CallStack.h"
#include "Meta/Any.h"

class NetNode;
class Process;

class RemotePlayer : public QObject, public Singleton<RemotePlayer>
{
    Q_OBJECT

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
    Set<int> GetBreakpoints(std::string source);
    void SetBreakpoints(std::string source, Set<int> lines);

signals:
    void Break();
    void StateChanged();

private:
    void CustomNetWork();
    void OnGetMessage(Any& message);

public:
    CallStack stack;

private:
    Process* process;
    NetNode* netNode;
    Breakpoints breakpoints;
    bool isPaused;
};
