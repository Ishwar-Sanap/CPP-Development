#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <csignal>
#include "lin.h"

#define MAX_EVENTS 100
#define BUFFER_SIZE 1024

const int VALID_USER = 100;
const int ERR_INVALID_USER = 101;

/*

**************************************************************
epoll is a fast I/O event notification system provided by the Linux kernel.
Its job is to efficiently monitor thousands of sockets (or file descriptors) at the same time without using thousands of threads.

-  EPOLL is a Linux kernel mechanism for scalable, high-performance, event-driven servers.
-  It Using non-blocking I/O + readiness events
-👉 epoll tells your program WHEN a socket is ready for read/write,
so your program does NOT need:
    blocking read/write
    thousands of threads
    constant polling (waste CPU)


**************************************************************
Why epoll is better??

Problem 1 Fixed → No blocking on slow clients
If client sends no data → skip
Server continues, No thread blocks, No waiting..

Problem 2 Fixed → No need for many threads

You can handle 10,000 clients with:
 One or Two threads only

Problem 3 Fixed → Huge scalability

Thread pool = 100–200 connections
epoll = 100,000+ connections
so it used by epoll is used by:
Nginx,HAProxy,Redis,Node.js

**************************************************************
EPOLL Working Model
**************************************************************

Step 1 — Create epoll instance
int epfd = epoll_create1(0);

Step 2 — Register sockets you want to monitor
epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);

Step 3 — Wait for events
int n = epoll_wait(epfd, events, MAX_EVENTS, -1);
👉 This tells you exactly WHICH sockets have data.

Step 4 — Process only ready sockets
for (int i = 0; i < n; i++) {
    if (events[i].events & EPOLLIN) {
        read(events[i].data.fd, buffer, sizeof(buffer));
    }
}
**************************************************************

*/
LinServer::LinServer() : m_serverFD(-1), m_epollFD(-1)
{
}

LinServer::~LinServer()
{
    if (m_serverFD != -1)
        close(m_serverFD);
    if (m_epollFD != -1)
        close(m_epollFD);

    for (auto &kv : m_mapFDtoClient)
    {
        close(kv.first);
    }

    m_mapFDtoClient.clear();
}

bool LinServer::m_running = true;

// helper function
void LinServer::handle_sigint(int)
{
    m_running = false;
}

bool LinServer::initialize(int port)
{
    m_serverFD = socket(AF_INET, SOCK_STREAM, 0);
    if (m_serverFD < 0)
    {
        cout << "Socket creation failed" << endl;
        return false;
    }

    int opt = 1;

    // set socket options to resue the address and port, after termination of process same port will immediateley available.
    setsockopt(m_serverFD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    setsockopt(m_serverFD, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    setSocketNonBlocking(m_serverFD);

    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET; // IPV4
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(m_serverFD, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        cout << "Bind failed" << endl;
        return false;
    }

    if (listen(m_serverFD, SOMAXCONN) < 0)
    {
        cout << "Listen failed" << endl;
        return false;
    }

    m_epollFD = epoll_create1(0);
    if (m_epollFD == -1)
    {
        cout << "epoll_create1 failed" << endl;
        return false;
    }

    epoll_event ev{};
    ev.events = EPOLLIN; // Level-triggered for the listening server socket
    ev.data.fd = m_serverFD;
    if (epoll_ctl(m_epollFD, EPOLL_CTL_ADD, m_serverFD, &ev) < 0) // Add server socket to epoll for monitoring
    {
        cout << "unable to server socket to epoll for monitoring " << endl;
        return false;
    }

    cout << "Server is listening on port : " << port << endl;
    return true;
}

void LinServer::exeuteCommand(string &command, int clientFD)
{
    // Executing the command using popen()
    string output;
    if (command.find(";") != std::string::npos || command.find("|") != std::string::npos)
    {
        std::string err_msg = "Error: Command chaining not allowed.\n";
        send(clientFD, err_msg.c_str(), err_msg.length(), 0);
        close(clientFD);
        epoll_ctl(m_epollFD, EPOLL_CTL_DEL, clientFD, nullptr);
        m_mapFDtoClient.erase(clientFD);
        return;
    }
    if (command.length() > BUFFER_SIZE - 1)
    {
        std::string err_msg = "Error: Command too long.\n";
        send(clientFD, err_msg.c_str(), err_msg.length(), 0);
        return;
    }

    cout << "Recieved command : [" << command << "] for client  " << clientFD << endl;

    FILE *pipe_fp = popen(command.c_str(), "r");
    if (!pipe_fp)
    {
        std::string err_msg = "Error: failed to execute command.\n";
        send(clientFD, err_msg.c_str(), err_msg.length(), 0);
        return;
    }

    char pipe_buffer[BUFFER_SIZE];

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
        int bytesSend = send(clientFD, output.c_str() + totalSend, bytesToSend, 0);

        if (bytesSend == -1)
            break;

        totalSend += bytesSend;
    }
}

bool LinServer::setSocketNonBlocking(int socketID)
{
    // The fcntl() function in C++ is a POSIX system call used to perform various control operations on an open file descriptor

    /*
        Make a socket/file non-blocking
        EPOLL requires non-blocking sockets, otherwise your server hangs.

    */
    int flags = fcntl(socketID, F_GETFL, 0);

    if (flags == -1)
    {
        cout << "Error getting socket flags !" << endl;
        return false;
    }

    // using OR Bitwise operator the flag will be TURN ON
    flags = flags | O_NONBLOCK;

    // setting socket for non blocking using flags
    if (fcntl(socketID, F_SETFL, flags) == -1)
    {
        cout << "Error setting socket to non-blocking " << endl;
        return false;
    }
    /*
        How Non Blocking socket works???
        All socket calls return immediately.

        Ex:
        recv() behavior (non-blocking):

        No data? → returns -1 and errno = EAGAIN

        Some data? → returns immediately with available bytes

        accept() behavior (non-blocking):

        No pending client? → -1 + EAGAIN

        New client? → returns the fd instantly

        send() behavior (non-blocking):

        Buffer full? → EAGAIN, you retry later
        (no blocking → no hang)
    */

    return true;
}

void LinServer::handleNewConnection()
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int client_fd = accept(m_serverFD, (struct sockaddr *)&client_addr, &addr_len);
    if (client_fd >= 0)
    {
        setSocketNonBlocking(client_fd);
        epoll_event client_ev{};
        client_ev.events = EPOLLIN | EPOLLET; // Edge-triggered for client sockets
        client_ev.data.fd = client_fd;

        epoll_ctl(m_epollFD, EPOLL_CTL_ADD, client_fd, &client_ev); // Add client socket to epoll for monitoring

        m_mapFDtoClient[client_fd] = false; // Storing the new clinet verification details in map
    }
}

bool LinServer::isValidUser(string &data)
{
    int pos = data.find(" ");
    string name = data.substr(0, pos);
    string pass = data.substr(pos + 1);

    cout << name << " " << pass << endl;

    if (name == "Admin" && pass == "Admin@123")
        return true;

    return false;
}

void LinServer::handleClientEvent(int fd)
{
    char buf[BUFFER_SIZE] = {0};
    ssize_t bytes = read(fd, buf, sizeof(buf) - 1);

    if (bytes <= 0)
    {
        close(fd);
        epoll_ctl(m_epollFD, EPOLL_CTL_DEL, fd, nullptr); // Remove a file descriptor from epoll monitoring.
        m_mapFDtoClient.erase(fd);
        return;
    }

    buf[bytes] = '\0';
    string command(buf);

    bool verified = m_mapFDtoClient[fd];

    if (!verified)
    {
        if (isValidUser(command))
        {
            m_mapFDtoClient[fd] = true;
            string res = to_string(VALID_USER);
            send(fd, res.c_str(), res.length(), 0);
        }
        else
        {
            string res = to_string(ERR_INVALID_USER);
            send(fd, res.c_str(), res.length(), 0);
        }


        return;
    }

    exeuteCommand(command, fd);
}

void LinServer::start()
{
    epoll_event events[MAX_EVENTS];

    // Register signal handlers for graceful shutdown like CTR+C or termination signal
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigint);

    while (m_running)
    {
        /*
        Wait for events on an epoll instance "epoll_fd". Returns the number of
        triggered events returned in "events" buffer. Or -1 in case of
        error

        blocks until at least one socket is ready to read/write
        */
        int event_count = epoll_wait(m_epollFD, events, MAX_EVENTS, -1);

        for (int i = 0; i < event_count; ++i)
        {
            int fd = events[i].data.fd;
            if (fd == m_serverFD)
            {
                handleNewConnection();
            }
            else
            {
                handleClientEvent(fd);
            }
        }
    }

    cout << "\nServer shut down gracefully." << endl;
}