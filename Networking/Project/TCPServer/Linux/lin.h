
#ifndef LINSERVER_H
#define LINSERVER_H

#include <iostream>
#include <thread>
#include <unordered_map>
#include "tcpserver.h"
using namespace std;

class LinServer : public TCPServer
{
private:
    int m_serverFD;
    int m_epollFD;
    static bool m_running;
    unordered_map<int, bool> m_mapFDtoClient;
    void handleClientEvent(int socketFD);
    void handleNewConnection();
    bool isValidUser(string &data);
    bool setSocketNonBlocking(int socketFD);
    void exeuteCommand(string &cmd, int socketFD);
    static void handle_sigint(int);
public:
    LinServer();
    ~LinServer();
    bool initialize(int port) override;
    void start() override;
};

#endif // LINSERVER_H