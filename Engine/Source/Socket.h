
#pragma once

#include <string>

class Socket
{
public:
    Socket();
    ~Socket();

    void Host(int port);
    bool Connect(std::string host, int port);

    void Send(char* buffer);
    char* Read();

private:
    int handle;
};
