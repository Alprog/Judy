
#pragma once

#include <string>

class Socket abstract
{
public:
    static Socket* Create();

public:
    virtual bool SetBlockingMode(bool value) = 0;
    virtual void Listen(int port) = 0;
    virtual bool Accept() = 0;
    virtual bool Connect(std::string host, int port) = 0;
    virtual int Send(const char* buffer, int length) = 0;
    virtual int Receive(char* buffer, int max) = 0;
};
