#include "tcpserver.h"

#ifdef PLATFORM_WINDOWS
#include "Windows/win.h"
#elif defined(PLATFORM_LINUX)
#include "Linux/lin.h"

#endif


//static method for creating server..
TCPServer *TCPServer::createServer()
{
#ifdef PLATFORM_WINDOWS
    return new winServer();
#elif defined(PLATFORM_LINUX)
    return new LinServer();
#endif
}
