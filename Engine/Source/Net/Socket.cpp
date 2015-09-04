
//#include <cstring>

//    #include <sys/socket.h>
//    #include <netinet/in.h>
//    #include <arpa/inet.h>
//    #include <sys/ioctl.h>

//    #define NO_ERROR 0;

#include "Socket.h"
#include "Platforms.h"

Socket* Socket::Create()
{
    return new PlatformSocket();
}
