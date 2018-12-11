
#include "PlatformSocket.h"

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

bool UnixSocket::setBlockingMode(bool value)
{
    auto mode = value ? 0ul : 1ul;
    auto result = ioctl(handle, FIONBIO, &mode);
    return result == 0;
}

void UnixSocket::listen(int port)
{
    struct sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = INADDR_ANY;
    adress.sin_port = htons(port);

    auto result = bind(handle, (sockaddr*)&adress, sizeof(adress));
    if (result == 0)
    {
        ::listen(handle, 2);
    }
    else
    {
        if (errno == EADDRINUSE)
        {
            _exit(1);
        }
    }
}

Socket* UnixSocket::accept()
{
    struct sockaddr_in clientAddress;
    auto clientSize = (socklen_t)sizeof(clientAddress);
    auto clientSocket = ::accept(handle, (sockaddr*)&clientAddress, &clientSize);
    if (clientSocket <= 0)
    {
        return nullptr;
    }
    return new UnixSocket(clientSocket);
}

bool UnixSocket::connect(std::string host, int port)
{
    struct sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = inet_addr(host.c_str());
    adress.sin_port = htons(port);
    auto result = ::connect(handle, (sockaddr*)&adress, sizeof(adress));
    return result == 0;
}

int UnixSocket::send(const char* buffer, int length)
{
    return ::send(handle, buffer, length, 0);
}

int UnixSocket::receive(char* buffer, int max)
{
    return recv(handle, buffer, max, 0);
}

Socket::Error UnixSocket::getLastError()
{
    switch (errno)
    {   
        case EWOULDBLOCK:
            return Error::WouldBlock;

        case EISCONN:
            return Error::AlreadyConnected;

        case EINVAL:
            return Error::InvalidArgument;

        default:
            return Error::Unknown;
    }
}

