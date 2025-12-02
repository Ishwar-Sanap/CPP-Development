#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <string>

//Base class of TCPServer
class TCPServer
{
public:
    virtual bool initialize(int port) = 0;
    virtual void start() = 0;
    virtual ~TCPServer() = default;

    // Factory function to create server instances
    static TCPServer *createServer();
};
#endif //TCPSERVER_H