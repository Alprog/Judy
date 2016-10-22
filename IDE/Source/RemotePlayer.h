
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
    void run();
    void stop();

    bool isRunning();
    bool isConnected();
    bool isPaused();

    void sendCommand(std::string name);
    CallInfo* getActiveCall();
    Set<int> getBreakpoints(std::string source);
    void setBreakpoints(std::string source, Set<int> lines);

signals:
    void stateChanged();

private:
    void customNetWork();
    void onGetMessage(Any& message);

public:
    CallStack stack;

private:
    Process* process;
    NetNode* netNode;
    Breakpoints breakpoints;
    bool isPausedFlag;
};
