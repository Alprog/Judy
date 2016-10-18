
#pragma once

#include "Net/Socket.h"

class UnixSocket : public Socket
{
public:
    UnixSocket();
    UnixSocket(int handle);
    ~UnixSocket();

    virtual bool setBlockingMode(bool value) override;
    virtual void listen(int port) override;
    virtual Socket* accept() override;
    virtual bool connect(std::string host, int port) override;
    virtual int send(const char* buffer, int length) override;
    virtual int receive(char* buffer, int max) override;
    virtual Error getLastError() override;

private:
    int handle;
};
