#include "win.h"

// constructor
WinServer::WinServer()
{
}

// Destructor
WinServer::~WinServer()
{
}

bool WinServer::initialize(int port, const std::string &ip_address = "0.0.0.0")
{
    // TODO : creating the windows server
    // In windows there is no epoll mechanism for notifying events
    // we have to use IOCP

    return false;
}

void WinServer::start()
{
}