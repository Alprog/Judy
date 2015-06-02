
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

    bool Send(std::string& message);
    void Send(char* buffer);
    char* Receive();

private:
    unsigned int handle;
};
