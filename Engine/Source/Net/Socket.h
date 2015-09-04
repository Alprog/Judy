
#pragma once

#include <string>

class Socket abstract
{
protected:
    Socket();

public:
    static Socket* Create();

    enum class Error
    {
        Ok,
        WouldBlock,
        AlreadyConnected,
        Unknown
    };

public:
    virtual bool SetBlockingMode(bool value) = 0;
    virtual void Listen(int port) = 0;
    virtual Socket* Accept() = 0;
    virtual bool Connect(std::string host, int port) = 0;
    virtual int Send(const char* buffer, int length) = 0;
    virtual int Receive(char* buffer, int max) = 0;

    Error GetLastError();

protected:
    Error error;
};
