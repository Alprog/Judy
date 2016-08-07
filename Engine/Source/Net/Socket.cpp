
#include "Socket.h"
#include "Platforms.h"

Socket* Socket::Create()
{
    return new PlatformSocket();
}

Socket::~Socket()
{
}
