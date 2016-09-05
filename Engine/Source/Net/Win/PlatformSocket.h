
#pragma once

#include "Net/Socket.h"
#include <windows.h>

class WinSocket : public Socket
{
public:
    WinSocket();
    WinSocket(SOCKET handle);
    ~WinSocket();

    virtual bool SetBlockingMode(bool value) override;
    virtual void Listen(int port) override;
    virtual Socket* Accept() override;
    virtual bool Connect(std::string host, int port) override;
    virtual int Send(const char* buffer, int length) override;
    virtual int Receive(char* buffer, int max) override;
    virtual Error GetLastError() override;

private:
    SOCKET handle;
    static int count;
};

using PlatformSocket = WinSocket;
