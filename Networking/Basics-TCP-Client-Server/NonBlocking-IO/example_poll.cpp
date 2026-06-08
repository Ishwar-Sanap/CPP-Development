#include <iostream>
#include <poll.h>
#include <unistd.h>

/*
How it works internally
The kernel gets the array of pollfd structures.
It checks each descriptor for the requested event.
If none are ready, the process sleeps.
When one becomes ready, the kernel wakes the process.
Kernel fills revents so the program knows which descriptors are ready.


Data structure describing a polling request.  

strcut pollfd {
    int fd;         // file descriptor to monitor
    short events;   // events to monitor (e.g., POLLIN)
    short revents;  // events that occurred (set by kernel)
}
*/


int main()
{
    int sock1 = 3; // assume valid socket fds
    int sock2 = 4;

    // Create an array of pollfd structures to monitor multiple file descriptors
    // Each pollfd structure specifies a file descriptor and the events to monitor for that descriptor.
    //
    struct pollfd fds[2];
    fds[0].fd = sock1;
    fds[0].events = POLLIN; // POLLIN indicates that we want to monitor for data available to read on sock1

    fds[1].fd = sock2;
    fds[1].events = POLLIN;   // POLLIN indicates that we want to monitor for data available to read on sock2

    // poll() waits for one of the file descriptors to become active (e.g., data available to read).
    // It uses an array of pollfd structures to specify which file descriptors to monitor and what events to look for.
    // poll() is more efficient than select() for large numbers of file descriptors because it does not use bitmasks and can directly return the active descriptors.
    // returns the number of file descriptors that are ready, zero if timed out, or -1 for errors.

    // poll aslo takes o(n) time to check all descriptors, but it is more efficient than select for large numbers of descriptors.
    // poll(fd, nfds, timeout)
    int ready = poll(fds, 2, -1); // -1 means wait forever

    if (ready > 0)
    {
        if (fds[0].revents & POLLIN)
            std::cout << "sock1 has data\n";
        if (fds[1].revents & POLLIN)
            std::cout << "sock2 has data\n";
    }

    return 0;
}