
#include "WinSocket.h"

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
    auto result = ioctlsocket(handle, FIONBIO, &mode);
    return result == NO_ERROR;
}

void WinSocket::Listen(int port)
{
    struct sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = INADDR_ANY;
    adress.sin_port = htons(port);

    bind(handle, (sockaddr*)&adress, sizeof(adress));
    listen(handle, 2);
}

Socket* WinSocket::Accept()
{
    sockaddr clientAddress;
    int clientSize = sizeof(clientAddress);
    SOCKET clientSocket = accept(handle, &clientAddress, &clientSize);
    if (clientSocket == INVALID_SOCKET)
    {
        return nullptr;
    }
    return new WinSocket(clientSocket);
}

bool WinSocket::Connect(std::string host, int port)
{
    struct sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = inet_addr(host.c_str());
    adress.sin_port = htons(port);
    auto result = connect(handle, (sockaddr*)&adress, sizeof(adress));
    return result == NO_ERROR;
}

int WinSocket::Send(const char* buffer, int length)
{
    return send(handle, buffer, length, 0);
}

int WinSocket::Receive(char* buffer, int max)
{
    return recv(handle, buffer, max, 0);
}

Socket::Error WinSocket::GetLastError()
{
    int a = WSAGetLastError();
    switch (a)
    {
        case WSAEWOULDBLOCK:
            return Error::WouldBlock;

        case WSAEISCONN:
            return Error::AlreadyConnected;

        default:
            return Error::Unknown;
    }
}
