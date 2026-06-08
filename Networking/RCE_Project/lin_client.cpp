#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
using namespace std;

#define PORT_NUMBER 8095
#define SERVER_IP "127.0.0.1" // local host
#define BUFFER_SIZE 1024

// commands to compile: g++ lin_client.cpp -o linclient
// run : ./linclient

// client can execute remote linux machine commands
//  ex:
//  ls -l
//  pwd
//  whoami

const int ERR_INVALID_USER = 101;
const int VALID_USER = 100;

void sendRecvDataFromServer(int clientSocket)
{
    while (1)
    {
        string command;
        cout << "\nEnter the command (or type 'exit'): " << endl;
        getline(cin, command);

        if (command == "exit")
        {
            break;
        }

        if (command.empty())
        {
            continue;
        }

        int sbyteCount = send(clientSocket, command.c_str(), command.length(), 0);

        if (sbyteCount == -1)
        {
            cout << "Server send error: " << strerror(errno) << endl;
            return;
        }

        cout << " ---------- Command Output ----------- " << endl;

        // receiving and printing output from server..

        char receiveBuffer[BUFFER_SIZE];
        int bytesRecv = 0;
        bool outputRecv = false;
        while ((bytesRecv = recv(clientSocket, receiveBuffer, BUFFER_SIZE - 1, 0)) > 0)
        {
            outputRecv = true;

            cout << " Received data Bytes : " << bytesRecv << endl;

            // adding terminating character
            receiveBuffer[bytesRecv] = '\0';
            cout << receiveBuffer;

            // complete message received..
            if (bytesRecv < BUFFER_SIZE - 1)
            {
                break;
            }
        }

        if (!outputRecv && bytesRecv == 0)
        {
            cout << "Error : Server closed the connection " << endl;
            break;
        }
        else if (!outputRecv && bytesRecv < 0)
        {
            cout << "Error : Recv failed: " << strerror(errno) << endl;
            break;
        }

        cout << "----------------------------------" << endl;
    }
}

bool isValidUser(int clientSocket)
{
    string userName = "";
    string password = "";

    cout << "Enter username : " << endl;
    cin >> userName;
    cout << "Enter password : " << endl;
    cin >> password;

    string user_credentials = userName + " " + password;

    send(clientSocket, user_credentials.c_str(), user_credentials.length(), 0);

    char receiveBuffer[BUFFER_SIZE];
    int bytesRecv = recv(clientSocket, receiveBuffer, BUFFER_SIZE - 1, 0);
    receiveBuffer[bytesRecv] = '\0';
    string str(receiveBuffer);
    int resp = stoi(str);

    if (resp == ERR_INVALID_USER)
        return false;
    else if (resp == VALID_USER)
        return true;

    return false;
}

int main()
{
    // Create a socket
    int clientSocket;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Check for socket creation success
    if (clientSocket == -1)
    {
        cout << "Error at socket(): " << strerror(errno) << endl;
        return 1;
    }

    // connection to server
    struct sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(SERVER_IP);
    clientService.sin_port = htons(PORT_NUMBER);

    if (connect(clientSocket, (struct sockaddr *)&clientService, sizeof(clientService)) == -1)
    {
        cout << "Client: connect() - Failed to connect: " << strerror(errno) << endl;
        close(clientSocket);
        return 1;
    }
    else
    {
        while (!isValidUser(clientSocket))
        {
            cout << "Authentication failed, Try again !!" << endl;
        }

        cout << "Authentication succeeded, connecting to server..." << endl;
    }

    sendRecvDataFromServer(clientSocket);

    close(clientSocket);

    return 0;
}
