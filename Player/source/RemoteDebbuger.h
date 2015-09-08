
#pragma once

#include "Net/NetNode.h"

class RemoteDebbuger : public Singleton<RemoteDebbuger>
{
public:
    void Start(int port);

    static NetNode* netNode;
};
