#include <iostream>
#include <sys/select.h>
#include <unistd.h>

using namespace std;

int main()
{
    int sock1 = 3; // Assume valid sockets
    int sock2 = 4;

    fd_set readfds;

    while (true)
    {
        // FD_ZERO(&readfds) clears the set.
        FD_ZERO(&readfds);

        // FD_SET() adds a file descriptor to the set. Here we are adding sock1 and sock2 to the readfds set.
        FD_SET(sock1, &readfds);
        FD_SET(sock2, &readfds);

        int maxfd = max(sock1, sock2);

        // select() waits until one or more file descriptors become "ready" for I/O.
        //  It monitors multiple file descriptors, waiting for any of them to become active (e.g., data available to read).
        //  It uses bitmasks to specify which file descriptors to monitor for reading, writing, and exceptional conditions.
        // select() uses bitmasks (fd_set), so the time to check all descriptors is O(n) in the number of descriptors.

        // It can handle a limited number of file descriptors (typically 1024) due to the use of fixed-size bitmasks, which can be a limitation for applications that need to monitor many descriptors.
        int ready = select(maxfd + 1,
                           &readfds,
                           nullptr,
                           nullptr,
                           nullptr);

        if (ready < 0)
        {
            cout << "select failed\n";
            break;
        }
        /*

        If select() returns successfully:
            it returns the number of descriptors that are ready
            FD_ISSET(sock1, &readfds) tells you if sock1 is ready
            FD_ISSET(sock2, &readfds) tells you if sock2 is ready
        */

        if (FD_ISSET(sock1, &readfds))
        {
            cout << "Data available on sock1\n";
        }

        if (FD_ISSET(sock2, &readfds))
        {
            cout << "Data available on sock2\n";
        }
    }
}