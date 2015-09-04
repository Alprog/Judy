
#include "WinSocket.h"

#define ioctl ioctlsocket
using socklen_t = int;

int WinSocket::count = 0;

WinSocket::WinSocket()
{
    if (count == 0)
    {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    }
    count++;

    handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

WinSocket::WinSocket(SOCKET handle)
    : handle{handle}
{
    count++;
}

WinSocket::~WinSocket()
{
    closesocket(handle);
    count--;
    if (count == 0)
    {
        WSACleanup();
    }
}

bool WinSocket::SetBlockingMode(bool value)
{
    auto mode = value ? 0ul : 1ul;
    auto result = ioctl(handle, FIONBIO, &mode);
    return result == NO_ERROR;
}

void WinSocket::Listen(int port)
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

Socket* WinSocket::Accept()
{
    struct sockaddr_in clientAddress;
    int clientSize = sizeof(clientAddress);

    SOCKET clientSocket = accept(handle, (sockaddr*)&clientAddress, (socklen_t*)&clientSize);
    if (clientSocket == INVALID_SOCKET)
    {
        return nullptr;
    }
    else
    {
        return new WinSocket(clientSocket);
    }
}

bool WinSocket::Connect(std::string host, int port)
{
    struct sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = inet_addr(host.c_str());
    adress.sin_port = htons(port);
    auto result = connect(handle, (sockaddr*)&adress, sizeof(adress));
    if(result != NO_ERROR)
    {
        auto error = WSAGetLastError();
        if (error != WSAEISCONN)
        {
            return false;
        }
    }
    return true;
}

int WinSocket::Send(const char* buffer, int length)
{
    return send(handle, buffer, length, 0);
}

int WinSocket::Receive(char* buffer, int max)
{
    return recv(handle, buffer, max, 0);
}

void WinSocket::SetLastError()
{
    switch (WSAGetLastError())
    {
        case WSAEWOULDBLOCK:
            error = Socket::Error::WouldBlock;
            break;

        default:
            error = Socket::Error::Unknown;
            break;
    }
}
