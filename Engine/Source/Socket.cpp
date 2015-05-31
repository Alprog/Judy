
#include "Socket.h"

#include <winsock2.h>

Socket::Socket()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

Socket::~Socket()
{
    WSACleanup();
}

void Socket::Host(int port)
{
    struct sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = INADDR_ANY;
    adress.sin_port = htons(port);

    int size = (int)sizeof(adress);

    if (bind(handle, (sockaddr*)&adress, size))
    {
        throw;
    }

    if (listen(handle, 2))
    {
        throw;
    }

    struct sockaddr_in clientAddress;
    int clientSize = sizeof(clientAddress);
    handle = accept(handle, (struct sockaddr*)&clientAddress, (int*)&clientSize);
    if (handle == 0)
    {
        throw;
    }
}

bool Socket::Connect(std::string host, int port)
{
    struct sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = inet_addr(host.c_str());
    adress.sin_port = htons(port);
    return connect(handle, (sockaddr*)&adress, sizeof(adress)) == 0;
}

void Socket::Send(char* buffer)
{
    send(handle, buffer, strlen(buffer) + 1, 0);
}

char* Socket::Read()
{
    return nullptr;
}
