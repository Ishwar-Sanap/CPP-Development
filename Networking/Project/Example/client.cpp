#include <iostream>
#include "tcpclient.h"

#define PORT_NUMBER 8080

int main()
{
    TCPClient *client = TCPClient::createClient();

    if (client)
    {
        client->initialize(PORT_NUMBER);

        if (client->connectToServer())
        {
            client->communicateWithServer();
        }
        else
        {
            std::cout << "Unable to connect server " << std::endl;
        }
    }
    else
    {
        std::cout << "Failed to create server instances." << std::endl;
    }
}