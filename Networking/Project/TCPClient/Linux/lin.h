#ifndef LINCLIENT_H
#define LINCLIENT_H

#include <unistd.h>
#include <arpa/inet.h>
#include "tcpclient.h"

#define BUFFER_SIZE 1024

class LinClient : public TCPClient
{
private:
    int m_socketFD;
    struct sockaddr_in server_addr;

public:
    LinClient();
    ~LinClient();

    bool initialize(int port, const std::string &ip_address = "127.0.0.1") override;
    bool connectToServer() override;
    int communicateWithServer() override;
    bool isValidUser();

};
#endif