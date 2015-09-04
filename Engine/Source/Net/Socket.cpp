
#include "Socket.h"
#include "Platforms.h"

Socket::Socket()
    : error {Socket::Error::Ok}
{
}

Socket* Socket::Create()
{
    return new PlatformSocket();
}

Socket::Error Socket::GetLastError()
{
    return error;
}
