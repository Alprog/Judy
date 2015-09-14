
#pragma once

#include "Singleton.h"

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
    void Pause();
    void Continue();
    void Stop();

    bool IsRunning();
    bool IsConnected();
    bool IsPaused();

public:
    Process* process;
    NetNode* netNode;
    bool isPaused;
};
