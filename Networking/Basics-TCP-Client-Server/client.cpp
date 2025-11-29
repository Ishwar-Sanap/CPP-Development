#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

#define PORT_NUMBER 8095
#define SERVER_IP "192.168.1.3"

/*
STEPS for creating Clinets

1) create the socket
2) Define server address
3) Convert IP string → binary format suitable for nextwork
4) Connect to server
5) Send and recieve messages to server..


*/

int main()
{
    // 1. create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        cout << "Socket creation failed\n";
        return 1;
    }

    // 2. Define server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;          // IPV4
    server_addr.sin_port = htons(PORT_NUMBER); // htons() is used to converts the integer to Network Byte Order (big endian).

    // 3. Convert IP string → binary format
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0)
    {

        cout << "Invalid address/ address not supported !! \n";
        close(sock);
        return 1;
    }

    // 4. Connect to server
    /*
    It performs the TCP 3-way handshake with the server:
    Client → SYN →
       ← SYN-ACK ← Server
    Client → ACK →

    If this handshake succeeds → client gets connected to server.

    */
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        cout << "Connection failed\n";
        close(sock);
        return 1;
    }
    else
    {
        cout << " Connected with server ..." << endl;
    }

    // 5. Send message
    const char *msg = "Hello from client!";
    send(sock, msg, strlen(msg), 0);

    // 5. Receive response
    char buffer[1024] = {0};
    read(sock, buffer, sizeof(buffer));
    cout << "Server says: " << buffer << endl;

    close(sock);
    return 0;
}