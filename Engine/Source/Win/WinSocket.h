
#pragma once

#include "Net/Socket.h"
#include <windows.h>

class WinSocket : public Socket
{
public:
    WinSocket();
    ~WinSocket();

    bool SetBlockingMode(bool value) override;
    void Listen(int port) override;
    bool Accept() override;
    bool Connect(std::string host, int port) override;
    int Send(const char* buffer, int length) override;
    int Receive(char* buffer, int max) override;

private:
    SOCKET handle;

    static int count;
};
