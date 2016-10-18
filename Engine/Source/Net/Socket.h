
#pragma once

#include <string>

class Socket
{
public:
    static Socket* create();
    virtual ~Socket();

    enum class Error
    {
        Ok,
        WouldBlock,
        AlreadyConnected,
        InvalidArgument,
        Unknown
    };

    virtual bool setBlockingMode(bool value) = 0;
    virtual void listen(int port) = 0;
    virtual Socket* accept() = 0;
    virtual bool connect(std::string host, int port) = 0;
    virtual int send(const char* buffer, int length) = 0;
    virtual int receive(char* buffer, int max) = 0;
    virtual Error getLastError() = 0;
};
