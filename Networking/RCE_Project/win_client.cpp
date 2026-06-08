#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
using namespace std;

#define PORT_NUMBER 8095
#define SERVER_IP "127.0.0.1" // local host
#define BUFFER_SIZE 1024

// commands to compile only work on windows: g++ win_client.cpp -o winclinet -lws2_32
// run : ./winclinet

// client can execute remote linux machine commands
//  ex:
//  ls -l
//  pwd
//  whoami

const int ERR_INVALID_USER = 101;
const int VALID_USER = 100;

void sendRecvDataFromServer(SOCKET clientSocket)
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

        if (sbyteCount == SOCKET_ERROR)
        {
            cout << "Server send error: " << WSAGetLastError() << endl;
            return;
        }

        cout << " ---------- Command Output ----------- " << endl;

        // receiving and printing outupt from server..

        char receiveBuffer[BUFFER_SIZE];
        int bytesRecv = 0;
        bool outputRecv = false;
        while ((bytesRecv = recv(clientSocket, receiveBuffer, BUFFER_SIZE - 1, 0)) > 0)
        {
            outputRecv = true;

            cout << " Recieved data Bytes : " << bytesRecv << endl;

            // adding terminatining character
            receiveBuffer[bytesRecv] = '\0';
            cout << receiveBuffer;

            // complete message recived..
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
            cout << "Error : Recv failed" << endl;
            break;
        }

        cout << "----------------------------------" << endl;
    }
}

bool isValidUser(SOCKET clientSocket)
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
    // Initialize WSA variables
    WSADATA wsaData;
    int wserr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wserr = WSAStartup(wVersionRequested, &wsaData);

    // Check for initialization success
    if (wserr != 0)
    {
        cout << "The winsock dll not found" << endl;
        return 1;
    }

    // Create a socket
    SOCKET clientSocket;
    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Check for socket creation success
    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    // connection to server
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(SERVER_IP);
    clientService.sin_port = htons(PORT_NUMBER);

    if (connect(clientSocket, (SOCKADDR *)&clientService, sizeof(clientService)) == SOCKET_ERROR)
    {
        cout << "Client: connect() - Failed to connect: " << WSAGetLastError() << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    else
    {
        while (!isValidUser(clientSocket))
        {
            cout << "Authetication failed, Try agin !!" << endl;
        }

        cout << "Authetication succeed, connecting to server..." << endl;
    }

    sendRecvDataFromServer(clientSocket);

    closesocket(clientSocket);

    WSACleanup();

    return 0;
}