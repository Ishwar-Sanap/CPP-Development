#include <iostream>
#include <cstring>
#include "lin.h"
#include "clienterrors.h"

using namespace std;

LinClient::LinClient() : m_socketFD(-1)
{
}

LinClient::~LinClient()
{
    // closing the socket..
    if (m_socketFD != -1)
        close(m_socketFD);
}

bool LinClient::initialize(int port, const string &ip_address)
{
    m_socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socketFD < 0)
    {
        cout << "Socket creation failed\n";
        return false;
    }

    server_addr.sin_family = AF_INET;   // IPV4
    server_addr.sin_port = htons(port); // htons() is used to converts the integer to Network Byte Order (big endian).

    // 3. Convert IP string → binary format
    if (inet_pton(AF_INET, ip_address.c_str(), &server_addr.sin_addr) <= 0)
    {
        cout << "Invalid address or address not supported !! \n";
        close(m_socketFD);
        m_socketFD = -1;
        return false;
    }

    return true;
}

bool LinClient::connectToServer()
{
    if (connect(m_socketFD, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        cout << "Connection failed\n";
        close(m_socketFD);
        m_socketFD = -1;
        return false;
    }

    cout << "Connecting with server.." << endl;
    return true;
}

bool LinClient::isValidUser()
{
    string userName = "";
    string password = "";

    cout << "Enter username : " << endl;
    getline(cin, userName);

    cout << "Enter password : " << endl;
    getline(cin, password);

    string user_credentials = userName + " " + password;

    send(m_socketFD, user_credentials.c_str(), user_credentials.length(), 0);

    char receiveBuffer[BUFFER_SIZE];
    int bytesRecv = recv(m_socketFD, receiveBuffer, BUFFER_SIZE - 1, 0);
    receiveBuffer[bytesRecv] = '\0';

    string str(receiveBuffer);
    int resp = stoi(str);

    if (resp == VALID_USER)
        return true;

    return false;
}

int LinClient::communicateWithServer()
{
    int attempts = 3;

    while (attempts > 0 && !isValidUser())
    {
        attempts--;
        cout << "Authetication failed, attempts remaining " << attempts << " try again !" << endl;
    }

    if (attempts == 0)
    {
        return ERR_ATTEMPTS_OVER;
    }

    cout << "Authetication succeed.." << endl;

    while (true)
    {
        cout << "\nEnter the command (or type 'exit'): " << endl;
        string command;
        getline(cin, command); // read the entire line including space

        if (command == "exit")
        {
            break;
        }

        if (command.empty())
        {
            continue;
        }

        int sbyteCount = send(m_socketFD, command.c_str(), command.length(), 0);

        if (sbyteCount == -1)
        {
            cout<<"Error in sending data to server " << endl;
            return ERR_SEND;
        }

        cout << " ---------- Command Output ----------- " << endl;

        // receiving and printing outupt from server..

        char receiveBuffer[BUFFER_SIZE];
        int bytesRecv = 0;
        bool outputRecv = false;

        while ((bytesRecv = recv(m_socketFD, receiveBuffer, BUFFER_SIZE - 1, 0)) > 0)
        {
            outputRecv = true;
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
            cout<<"Server disconnected unexpectedly " << endl;
            return ERR_SERVER_DISCONNECTED;
        }
        else if (!outputRecv && bytesRecv < 0)
        {
            cout<<"Error in receiving data from server " << endl;
            return ERR_RECV;
        }

        cout << "----------------------------------" << endl;
    }

    return 0;
}