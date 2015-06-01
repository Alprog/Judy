
#pragma once

#include <string>

class Socket
{
public:
    Socket();
    ~Socket();

    bool SetBlockingMode(bool value);

    void Listen(int port);
    bool Accept();

    bool Connect(std::string host, int port);

    void Send(char* buffer);
    char* Read();

private:
    unsigned int handle;
};
