
#include "Socket.h"

#include <winsock2.h>

int count = 0;

Socket::Socket()
{
    if (count == 0)
    {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    }
    count++;

    handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

Socket::~Socket()
{
    count--;
    if (count == 0)
    {
        WSACleanup();
    }
}

bool Socket::SetBlockingMode(bool value)
{
    auto mode = value ? 0ul : 1ul;
    auto result = ioctlsocket(handle, FIONBIO, &mode);
    return result == NO_ERROR;
}

void Socket::Listen(int port)
{
    struct sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = INADDR_ANY;
    adress.sin_port = htons(port);

    int size = (int)sizeof(adress);

    if (bind(handle, (sockaddr*)&adress, size))
    {
        printf("!");
        throw;
    }

    if (listen(handle, 2))
    {
        printf("@");
        throw;
    }
}

bool Socket::Accept()
{
    struct sockaddr_in clientAddress;
    int clientSize = sizeof(clientAddress);

    SOCKET clientSocket = accept(handle, (struct sockaddr*)&clientAddress, (int*)&clientSize);
    if (clientSocket == INVALID_SOCKET)
    {
        if (WSAGetLastError() == WSAEWOULDBLOCK)
        {

        }
        return false;
    }

    return true;
}

bool Socket::Connect(std::string host, int port)
{
    struct sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = inet_addr(host.c_str());
    adress.sin_port = htons(port);

    //getaddrinfo();

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
