#include "tcpclient.h"

#ifdef PLATFORM_WINDOWS
#include "Windows/win.h"
#elif defined(PLATFORM_LINUX)
#include "Linux/lin.h"

// static method for creating server..
TCPClient *TCPClient::createClient()
{
#ifdef PLATFORM_WINDOWS
    return new winClient();
#elif defined(PLATFORM_LINUX)
    return new LinClient();
#endif
}

#endif