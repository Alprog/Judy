
#include "UnixSocket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>

UnixSocket::UnixSocket()
{
    handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // allow reuse
    int value = 1;
    setsockopt(handle, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
}

UnixSocket::UnixSocket(int handle)
    : handle{handle}
{
}

UnixSocket::~UnixSocket()
{
    close(handle);
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

    auto result = bind(handle, (sockaddr*)&adress, sizeof(adress));
    if (result == 0)
    {
        listen(handle, 2);
    }
    else
    {
        if (errno == EADDRINUSE)
        {
            exit(1);
        }
    }
}

Socket* UnixSocket::Accept()
{
    struct sockaddr_in clientAddress;
    auto clientSize = (socklen_t)sizeof(clientAddress);
    auto clientSocket = accept(handle, (sockaddr*)&clientAddress, &clientSize);
    if (clientSocket <= 0)
    {
        return nullptr;
    }
    return new UnixSocket(clientSocket);
}

bool UnixSocket::Connect(std::string host, int port)
{
    struct sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = inet_addr(host.c_str());
    adress.sin_port = htons(port);
    auto result = connect(handle, (sockaddr*)&adress, sizeof(adress));
    return result == 0;
}

int UnixSocket::Send(const char* buffer, int length)
{
    return send(handle, buffer, length, 0);
}

int UnixSocket::Receive(char* buffer, int max)
{
    return recv(handle, buffer, max, 0);
}

Socket::Error UnixSocket::GetLastError()
{
    switch (errno)
    {
        case EWOULDBLOCK:
            return Error::WouldBlock;

        case EISCONN:
            return Error::AlreadyConnected;

        default:
            return Error::Unknown;
    }
}

