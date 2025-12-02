#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <string>

//Base class of TCPClient
class TCPClient
{
public:
    virtual bool initialize(int port, const std::string& ip_address = "127.0.0.1") = 0;
    virtual bool connectToServer() = 0;
    virtual int communicateWithServer() = 0;
    virtual ~TCPClient() = default;

      // Factory function to create client instances
    static TCPClient *createClient();
};
#endif //TCPCLIENT_H