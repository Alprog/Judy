
#include <Socket.h>
#include <PlatformSocket.h>

Socket* Socket::Create()
{
    return new PlatformSocket();
}

Socket::~Socket()
{
}
