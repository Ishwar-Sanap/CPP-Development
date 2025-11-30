#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include "ctpl_stl.h"
using namespace std;

#define PORT_NUMBER 8095
#define BACKLOG_SIZE 5 // how many pending client connections waiting in queue.
#define BUFFER_SIZE 1024

const int ERR_INVALID_USER = 101;
const int VALID_USER = 100;
// Remote command execution server..
// Using Threadpool to handle multiple clients

bool isValidUser(string &credentials)
{
    int pos = credentials.find(" ");
    string name = credentials.substr(0, pos);
    string pass = credentials.substr(pos + 1);

    cout << name << " " << pass << endl;

    if (name == "Admin" && pass == "Admin@123")
        return true;

    return false;
}
void handleClient(int sockID, int tID)
{
    char buffer[BUFFER_SIZE] = {0};
    FILE *pipe_fp;
    ssize_t bytesRead;

    bool userVerified = false;

    while (true)
    {
        // blocking call
        bytesRead = read(sockID, buffer, sizeof(buffer));
        if (bytesRead <= 0)
        {
            cout << "Read error..." << endl;
            break;
        }
        buffer[bytesRead] = '\0'; // adding terminating character
        string command(buffer);

        if (!userVerified)
        {
            if (isValidUser(command))
            {
                userVerified = true;
                string res = to_string(VALID_USER);
                send(sockID, res.c_str(), res.length(), 0);

                cout << "Client connected Thread ID : " << tID << endl;
            }
            else{

                string res = to_string(ERR_INVALID_USER);
                send(sockID, res.c_str(), res.length(), 0);
            }

            continue;
        }

        if (command.find(";") != string::npos || command.find("|") != string::npos)
        {
            string err_msg = "Error: Command chaining not allowed.\n";
            send(sockID, err_msg.c_str(), err_msg.length(), 0);

            cout << "Rejected malicious command: " << command << endl;
            break;
        }

        cout << "Recieved command : [" << command << "]" << endl;

        // Executing the command using popen()
        pipe_fp = popen(command.c_str(), "r");

        if (!pipe_fp)
        {
            string err_msg = "Error: failed to execute command.\n";
            send(sockID, err_msg.c_str(), err_msg.length(), 0);
            break;
        }

        char pipe_buffer[BUFFER_SIZE];
        string output;

        while (fgets(pipe_buffer, BUFFER_SIZE, pipe_fp) != nullptr)
        {
            output += pipe_buffer;
        }

        pclose(pipe_fp);

        if (output.length() == 0)
        {
            output = "Command executed, but no output produeced\n";
        }

        int dataSize = output.size();
        int totalSend = 0;

        while (totalSend < dataSize)
        {
            int bytesToSend = dataSize - totalSend;

            int bytesSend = send(sockID, output.c_str() + totalSend, bytesToSend, 0);

            if (bytesSend == -1)
            {
                cout << "send failed" << endl;
                break;
            }

            totalSend += bytesSend;
        }
    }

    close(sockID);
    cout << "Client disconnected Thread ID : " << tID << endl;
}

int main()
{
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    int MAX_THREDS = 8;
    ctpl::thread_pool tp(MAX_THREDS);

    // 1. Create socket for server, so it will listen the client requests
    server_fd = socket(AF_INET, SOCK_STREAM, 0); // Creating the socket for  TCP IP protocol (SOCK_STREAM)
    if (server_fd < 0)
    {
        cout << "Socket creation failed\n";
        return 1;
    }

    int opt = 1;
    // set socket options to resue the address and port, after termination of process same port will immediateley available..
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        cout << "setsockopt SO_REUSEADDR failed!" << endl;
        close(server_fd);
        return 1;
    }

    // Set SO_REUSEPORT
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0)
    {
        cout << "setsockopt SO_REUSEPORT failed!" << endl;
        close(server_fd);
        return 1;
    }

    // 2. Define server address
    server_addr.sin_family = AF_INET;         // using IPv4 address family.  (AF_INET6 --> IPv6)
    server_addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0  //Address to accept any incoming messages through local networks interfaces

    server_addr.sin_port = htons(PORT_NUMBER); // sets the port number, //htons() is used to converts the integer to Network Byte Order (big endian).

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
    while (true)
    {
        cout << "waiting for accept" << endl;
        client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);

        if (client_socket < 0)
        {
            cout << "Accept failed try again for connection..\n";
            continue;
        }

        tp.push([client_socket](int tID)
                { handleClient(client_socket, tID); });
    }

    close(server_fd);

    return 0;
}
