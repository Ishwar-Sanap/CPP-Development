#include <iostream>
#include <sys/epoll.h> // epoll related APIs
#include <unistd.h>    // close()

using namespace std;

int main()
{
    int sock1 = 3; // Assume these are valid socket FDs
    int sock2 = 4;

    /****************** IMP NOTE ***************** */
    // Before using sock1, and sock2 we would typically set them up as non-blocking sockets
    // It means that read/write calls on these sockets will return immediately if they cannot proceed, instead of blocking the process.
    // This is important for using with epoll, as epoll is designed to work efficiently
    // with non-blocking file descriptors.
    // We can set a socket to non-blocking mode using fcntl() system call

    // --------------------------------------------------
    // SYSTEM CALL: epoll_create1()
    //
    // Creates an epoll instance inside the kernel.
    //
    // Kernel allocates:
    //    1. Interest List (FDs being monitored)
    //    2. Ready List (FDs ready for I/O)
    //
    // Returns:
    //    epoll file descriptor
    //
    // Similar to:
    //    open("/some/kernel/object")
    //
    // This FD is used in future epoll operations.
    // --------------------------------------------------
    int epfd = epoll_create1(0);

    if (epfd == -1)
    {
        perror("epoll_create1");
        return 1;
    }

    // Structure describing an event
    epoll_event ev;

    // --------------------------------------------------
    // Event type we want to monitor
    //
    // EPOLLIN:
    //     Notify when data becomes available to read.
    //
    // Other common events:
    //
    // EPOLLOUT
    //     Socket ready for writing.
    //
    // EPOLLERR
    //     Error occurred.
    //
    // EPOLLHUP
    //     Connection closed.
    // --------------------------------------------------
    ev.events = EPOLLIN;

    // User data returned later by epoll_wait()
    ev.data.fd = sock1;

    // --------------------------------------------------
    // SYSTEM CALL: epoll_ctl()
    //
    // Controls epoll interest list.
    //
    // Syntax:
    //
    // epoll_ctl(epfd,
    //           operation,
    //           target_fd,
    //           event_info)
    //
    // EPOLL_CTL_ADD
    //     Add FD to monitoring list.
    //
    // EPOLL_CTL_MOD
    //     Modify monitored events.
    //
    // EPOLL_CTL_DEL
    //     Remove FD.
    //
    // Kernel stores:
    //   sock1 --> EPOLLIN
    // in the interest list, It uses red-black tree data structure for efficient add/remove operations.
    // --------------------------------------------------
    epoll_ctl(epfd,
              EPOLL_CTL_ADD,
              sock1,
              &ev);

    // Register second socket
    ev.data.fd = sock2;

    epoll_ctl(epfd,
              EPOLL_CTL_ADD,
              sock2,
              &ev);

    // Buffer where kernel will place ready events
    epoll_event events[10];

    while (true)
    {
        // --------------------------------------------------
        // SYSTEM CALL: epoll_wait()
        //
        // Waits until one or more monitored FDs become ready.
        //
        // Arguments:
        //
        // epfd
        //     epoll instance FD
        //
        // events
        //     output array filled by kernel
        //
        // 10
        //     max events to return
        //
        // -1
        //     timeout
        //
        //     -1  -> wait forever
        //      0  -> return immediately
        //   5000 -> wait 5 seconds
        //
        // Return value:
        //
        // Number of ready events
        //
        // Example:
        //
        // sock1 receives data
        //
        // Kernel puts:
        //
        // events[0].data.fd = sock1
        //
        // and wakes up process.
        // --------------------------------------------------
        int n = epoll_wait(epfd,
                           events,
                           10,
                           -1);

        if (n == -1)
        {
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < n; i++)
        {
            int fd = events[i].data.fd;

            cout << "Ready FD = "
                 << fd
                 << endl;

            // Normally we'd call:
            //
            // read(fd, ...)
            //
            // because epoll told us data is available.
        }
    }

    // --------------------------------------------------
    // SYSTEM CALL: close()
    //
    // Releases kernel resources associated with FD.
    //
    // Removes epoll instance from kernel.
    // --------------------------------------------------
    close(epfd);

    return 0;
}