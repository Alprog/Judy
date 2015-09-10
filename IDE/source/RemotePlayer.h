
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

    void Break();
    void Continue();

    void Stop();

private:
    Process* process;
    NetNode* netNode;
};
