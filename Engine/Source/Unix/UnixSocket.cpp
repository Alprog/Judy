
#include "UnixSocket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

UnixSocket::UnixSocket()
{
    handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

UnixSocket::~UnixSocket()
{
    closesocket(handle);
}

bool UnixSocket::SetBlockingMode(bool value)
{
    auto mode = value ? 0ul : 1ul;
    auto result = ioctl(handle, FIONBIO, &mode);
    return result == 0;
}

void UnixSocket::Listen(int port)
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

bool UnixSocket::Accept()
{
    struct sockaddr_in clientAddress;
    int clientSize = sizeof(clientAddress);

    SOCKET clientSocket = accept(handle, (sockaddr*)&clientAddress, (socklen_t*)&clientSize);
    if (clientSocket == INVALID_SOCKET)
    {
        if (WSAGetLastError() == WSAEWOULDBLOCK)
        {

        }
        return false;
    }

    return true;
}

bool UnixSocket::Connect(std::string host, int port)
{
    struct sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = inet_addr(host.c_str());
    adress.sin_port = htons(port);
    auto result = connect(handle, (sockaddr*)&adress, sizeof(adress));
    return true;
}

int UnixSocket::Send(const char* buffer, int length)
{
    return send(handle, buffer, length, 0);
}

int UnixSocket::Receive(char* buffer, int max)
{
    return recv(handle, buffer, max, 0);
}
