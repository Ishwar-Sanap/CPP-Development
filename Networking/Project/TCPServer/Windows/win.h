#ifndef WINSERVER_H
#define WINSERVER_H

#include <iostream>
#include <string.h>
#include "tcpserver.h"

class WinServer : public TCPServer
{
public:
    WinServer();
    virtual ~WinServer();

    bool initialize(int port, const std::string &ip_address = "0.0.0.0") override;
    void start() override;
};

#endif