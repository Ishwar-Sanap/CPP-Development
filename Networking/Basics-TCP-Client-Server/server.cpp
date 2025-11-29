#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
using namespace std;

/*
STEPS To Write TCP Server:

1) Crerate a socket
2) Prepare server address and ports
3) Bind socket to IP + Port
4) Listen for new client connection
5) Accept client connection
6) Receive message from client
7) Send response to client
8) Close client sockcet


Below is simple template code for creating server
but actual server should run continously and should able to handle multiple clients..
so it can be done using mutithreding for handing differnt client
*/

#define PORT_NUMBER 8095
#define BACKLOG_SIZE 5 // how many pending client connections waiting in queue.

int main()
{
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // 1. Create socket for server, so it will listen the client requests
    server_fd = socket(AF_INET, SOCK_STREAM, 0); // Creating the socket for  TCP IP protocol (SOCK_STREAM)
    if (server_fd < 0)
    {
        cout << "Socket creation failed\n";
        return 1;
    }

    // 2. Define server address
    server_addr.sin_family = AF_INET;         // using IPv4 address family.  (AF_INET6 --> IPv6)
    server_addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0  //Address to accept any incoming messages through local networks interfaces

    server_addr.sin_port = htons(PORT_NUMBER); // sets the port number, //htons() is used to converts the integer to Network Byte Order (big endian).
    // Network packets always use big-endian order, but your CPU may use little-endian.

    // 3. Bind socket to IP/Port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        cout << "Bind failed\n";
        close(server_fd);
        return 1;
    }

    // 4. Listen for incoming connection
    if (listen(server_fd, BACKLOG_SIZE) < 0) // allow up to BACKLOG_SIZE pending client connections waiting in queue.
    {
        cout << "Listen failed\n";
        close(server_fd);
        return 1;
    }

    cout << "Server listening on port : " << PORT_NUMBER << endl;

    // 5. Accept client connection
    // This call block further execution until a client connects
    // This new socket is used for communication with that specific client.
    // Once TCP 3 way handshake (SYN → SYN-ACK → ACK)  completes → accept() returns
    client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);

    /*
    What happens inside OS after accept()?

    When a TCP connection is established:

    ✔ Kernel allocates Receive Buffer (for incoming data)
    ✔ Kernel allocates Send Buffer (for outgoing data)

    These buffers are part of the TCP stack inside the OS. Each connected socket has its own pair of buffers.
    Your read() or recv() call reads FROM this kernel buffer:
    */

    if (client_socket < 0)
    {
        cout << "Accept failed\n";
        close(server_fd);
        return 1;
    }

    cout << "Client connected!\n";

    // 6. Receive message
    char buffer[1024] = {0};

    //Blocks until data is received from the connected client.
    ssize_t retVal = read(client_socket, buffer, sizeof(buffer)); // return number of bytes read from kernel recieve buffer.. and read data stored in user buffer
    cout << "Client says: " << buffer << endl;

    // 7. Send reply
    const char *msg = "Hello from server....!";
    send(client_socket, msg, strlen(msg), 0);

    /*
    After send -->
    Data goes into OS send buffer first.
    Then TCP sends packets over network independently.
    Your program does NOT send packets directly — kernel handles it.
    */

    // 8. Close sockets
    close(client_socket);

    close(server_fd);

    return 0;
}
