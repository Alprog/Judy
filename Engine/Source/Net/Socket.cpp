
#include <Socket.h>
#include <PlatformSocket.h>

Socket* Socket::create()
{
    return new PlatformSocket();
}

Socket::~Socket()
{
}
