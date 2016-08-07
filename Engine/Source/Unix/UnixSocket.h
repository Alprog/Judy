
#pragma once

#include "Net/Socket.h"

class UnixSocket : public Socket
{
public:
    UnixSocket();
    UnixSocket(int handle);
    ~UnixSocket();

    virtual bool SetBlockingMode(bool value) override;
    virtual void Listen(int port) override;
    virtual Socket* Accept() override;
    virtual bool Connect(std::string host, int port) override;
    virtual int Send(const char* buffer, int length) override;
    virtual int Receive(char* buffer, int max) override;
    virtual Error GetLastError() override;

private:
    int handle;
};
