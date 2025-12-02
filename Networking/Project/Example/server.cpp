#include <iostream>
#include "tcpserver.h"

#define PORT_NUMBER 8080

int main()
{
    TCPServer *server = TCPServer::createServer();

    if (server)
    {
        // initialize the server with port and IP(optional)
        if (server->initialize(PORT_NUMBER))
        {
            server->start();
        }
        else
        {
            std::cout << "Failed to initialized server " << std::endl;
        }

        delete server;
        server = nullptr;
    }
    else
    {
        std::cout << "Failed to create server instances." << std::endl;
    }
}