
#pragma once

#include "Net/Socket.h"
#include <windows.h>

class WinSocket : public Socket
{
public:
    WinSocket();
    WinSocket(SOCKET handle);
    ~WinSocket();

    virtual bool setBlockingMode(bool value) override;
    virtual void listen(int port) override;
    virtual Socket* accept() override;
    virtual bool connect(std::string host, int port) override;
    virtual int send(const char* buffer, int length) override;
    virtual int receive(char* buffer, int max) override;
    virtual Error getLastError() override;

private:
    SOCKET handle;
    static int count;
};

using PlatformSocket = WinSocket;
