
#pragma once

#include "Singleton.h"
class NetNode;

class RemotePlayer : public Singleton<RemotePlayer>
{
    friend class Singleton<RemotePlayer>;

protected:
    RemotePlayer();

public:
    void Start();

    void Break();
    void Continue();

    void Stop();

private:
    NetNode* netNode;
};
