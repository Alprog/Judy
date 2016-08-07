
#pragma once

#include <string>

class Socket
{
public:
    static Socket* Create();
    virtual ~Socket();

    enum class Error
    {
        Ok,
        WouldBlock,
        AlreadyConnected,
        InvalidArgument,
        Unknown
    };

    virtual bool SetBlockingMode(bool value) = 0;
    virtual void Listen(int port) = 0;
    virtual Socket* Accept() = 0;
    virtual bool Connect(std::string host, int port) = 0;
    virtual int Send(const char* buffer, int length) = 0;
    virtual int Receive(char* buffer, int max) = 0;
    virtual Error GetLastError() = 0;
};
