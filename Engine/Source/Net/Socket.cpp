
#include "Socket.h"

#include <cstring>

#if WIN
    #include <winsock2.h>
    #define ioctl ioctlsocket
    using socklen_t = int;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/ioctl.h>

    #define NO_ERROR 0;
    using SOCKET = int;
#endif

int count = 0;

Socket::Socket()
{
#if WIN
    if (count == 0)
    {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    }
#endif
    count++;

    handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

Socket::~Socket()
{
    count--;
#if WIN
    if (count == 0)
    {
        WSACleanup();
    }
#endif
}

bool Socket::SetBlockingMode(bool value)
{
    auto mode = value ? 0ul : 1ul;   
    auto result = ioctl(handle, FIONBIO, &mode);
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

    SOCKET clientSocket = accept(handle, (sockaddr*)&clientAddress, (socklen_t*)&clientSize);
#if WIN
    if (clientSocket == INVALID_SOCKET)
    {
        if (WSAGetLastError() == WSAEWOULDBLOCK)
        {

        }
        return false;
    }
#endif

    return true;
}

bool Socket::Connect(std::string host, int port)
{
    struct sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = inet_addr(host.c_str());
    adress.sin_port = htons(port);
    auto result = connect(handle, (sockaddr*)&adress, sizeof(adress));
    return result == NO_ERROR;
}

int Socket::Send(const char* buffer, int length)
{
    return send(handle, buffer, length, 0);
}

int Socket::Receive(char* buffer, int max)
{
    return recv(handle, buffer, max, 0);
}

//bool Socket::Send(std::string& message)
//{
//    const char* buffer = message.c_str();

//    auto length = strlen(buffer) + 1;

//    int totalSend = 0;
//    while (totalSend < length)
//    {
//        int count = send(handle, buffer + totalSend, length - totalSend, 0);
//        if (count < 0)
//        {
//            return false;
//        }
//        totalSend += count;
//    }

//    return true;
//}

//void Socket::Send(char* buffer)
//{
//    send(handle, buffer, strlen(buffer) + 1, 0);
//}

//char* Socket::Receive()
//{
//    return nullptr;
//    //char[1024] buffer;
//    //recv(handle, buffer, max, 0);
//}
