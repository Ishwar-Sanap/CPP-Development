# Remote Command Execution Project (RCE_Project)

## Overview

This project implements a simple remote command execution system using TCP sockets.
The system consists of:
- a Linux server (`RCE_Server.cpp`) that accepts client connections, authenticates users, and executes shell commands
- a Linux client (`lin_client.cpp`) that connects to the server, sends credentials, and sends commands
- a Windows client example (`win_client.cpp`) showing equivalent functionality using Winsock
- a thread-pool header (`ctpl_stl.h`) used by the server for concurrent client handling

> The project is intended for learning socket programming, multithreading, client/server communication, and basic remote command execution.

## Files

- `RCE_Server.cpp`
  - Main server implementation for TCP connection handling, authentication, command execution, and response delivery.
- `lin_client.cpp`
  - Linux client implementation for connecting, authenticating, sending commands, and receiving output.
- `win_client.cpp`
  - Windows client implementation using Winsock APIs for cross-platform comparison.
- `ctpl_stl.h`
  - A lightweight C++ thread pool utility used by the server.

## Architecture

The RCE system follows a standard TCP client-server architecture:

1. Server starts and listens on port `8095`.
2. Client connects to the server.
3. Client sends authentication credentials as a single string.
4. Server validates the credentials.
5. If authentication succeeds, the client enters a command loop.
6. Client sends shell commands to the server.
7. Server executes commands using `popen()`.
8. Server sends command output back to the client.
9. Client displays the received output.

This architecture is designed for sequential command execution per connection, with one authenticated client session per socket.

## Server: `RCE_Server.cpp`

### Key concepts

- TCP socket creation with `socket(AF_INET, SOCK_STREAM, 0)`
- Reuse socket address and port with `setsockopt(SO_REUSEADDR)` and `setsockopt(SO_REUSEPORT)`
- Bind to `INADDR_ANY` so the server listens on all local interfaces
- Listen with backlog size `5`
- Accept connections with `accept()`
- Use a thread pool (`ctpl::thread_pool`) to handle client sessions concurrently
- Use `read()` and `send()` to communicate over the connected socket
- Execute shell commands with `popen()` and capture output
- Close client sockets when the session ends

### Authentication

The first message sent by the client is treated as credentials in the format:

```
username password
```

The server validates the credentials with `isValidUser()`:
- Accepts only `Admin Admin@123`
- Sends back `100` for valid credentials
- Sends back `101` for invalid credentials

### Client handling in `handleClient()`

- Read raw bytes from the socket using `read()` into a fixed-size buffer
- Convert the bytes to a `std::string`
- If user is not yet verified:
  - validate credentials
  - send the appropriate numeric response
  - keep the session open for command execution
- Once authenticated:
  - reject commands containing `;` or `|` as a minimal command chaining filter
  - execute the command using `popen()`
  - collect output line-by-line from `fgets()`
  - if no output is produced, send a fallback message
  - send the full command output back to the client in one or more `send()` calls
- Close the socket and log disconnects

### Thread pool

The server creates a thread pool with `MAX_THREDS = 8`.
Each accepted client connection is dispatched to the pool:

```cpp
tp.push([client_socket](int tID) { handleClient(client_socket, tID); });
```

This means multiple clients can be serviced concurrently without creating an unbounded number of threads.

## Linux Client: `lin_client.cpp`

### Key concepts

- Create a TCP socket with `socket(AF_INET, SOCK_STREAM, 0)`
- Connect to the server using `connect()`
- Send username and password as a single string
- Receive server authentication response with `recv()`
- Enter a loop reading commands from `std::getline()`
- Send command text to the server with `send()`
- Receive output from the server with `recv()` and print it
- Close the socket with `close()` when done

### Behavior

- Prompts for username and password
- Repeats authentication until it succeeds
- After authentication, repeatedly prompts for commands
- If the user enters `exit`, the client breaks the command loop and closes the socket
- Prints each chunk of server response as it arrives

## Windows Client: `win_client.cpp`

### Platform differences

The Windows client is the same remote-command concept, but uses Winsock:

- `WSAStartup()` and `WSACleanup()` for socket initialization
- `SOCKET` type instead of `int`
- `INVALID_SOCKET` and `SOCKET_ERROR` for error checks
- `closesocket()` instead of `close()`
- `WSAGetLastError()` for error codes

### Notes

This client is useful for comparing platform-specific socket initialization and cleanup.

## Communication Protocol

The protocol is a lightweight custom protocol over TCP:

1. Client connects to server.
2. Client sends credentials string.
3. Server replies with numeric status:
   - `100` = valid
   - `101` = invalid
4. If valid, client sends command strings.
5. Server sends raw command output as text.
6. Client displays received output.

There is no explicit message framing besides the TCP length delivered by `recv()`. This means the client assumes each `recv()` call receives a complete chunk of the server output, and the server assumes output fits in a looped `send()`.

## Build and Run

### Linux server

```bash
g++ RCE_Server.cpp -o RCE_Server -pthread
./RCE_Server
```

### Linux client

```bash
g++ lin_client.cpp -o linclient
./linclient
```

### Windows client

```bash
g++ win_client.cpp -o winclient -lws2_32
./winclient
```

## Interview Explanation

### High-level description

This project is a remote command execution system where a TCP client sends commands to a server. The server authenticates the client and executes shell commands on behalf of the client, returning the output.

### Server responsibilities

- listen for TCP connections
- authenticate the first client message
- accept commands from authenticated clients
- execute commands in the shell
- return output to the client
- handle multiple clients using a thread pool

### Client responsibilities

- connect to the server
- send credentials
- read command input from the user
- send commands to the server
- display server output

### Key APIs to mention

- `socket()`, `bind()`, `listen()`, `accept()`
- `connect()`, `send()`, `recv()`
- `setsockopt()` with `SO_REUSEADDR` and `SO_REUSEPORT`
- `popen()` for command execution on the server
- thread pool usage for concurrency

## Interview Talk Track

Use this short talk track when explaining the project:

- "This is a TCP client-server project for remote command execution."
- "The server listens on port `8095`, authenticates a client, and then executes commands sent by the authenticated client."
- "The Linux client sends credentials first, then enters a command loop where it sends commands and prints server output."
- "The server uses a thread pool so multiple clients can be handled concurrently without creating excessive threads."
- "Security is a concern: authentication is hardcoded, and shell execution via `popen()` is unsafe for production."

## Security Considerations

### Current risks

- authentication is hardcoded and insecure
- command execution uses `popen()` with raw input
- command filtering only blocks `;` and `|`
- no encryption or secure transport
- protocol is unauthenticated after the first message

### Recommended improvements

- use TLS/SSL for encryption
- authenticate using hashed credentials or tokens
- implement a command whitelist instead of arbitrary shell execution
- add proper message framing and length prefixes
- sanitize and validate command input carefully
- use a secure sandbox or restricted execution environment instead of direct `popen()`

## Project Summary

This project is a good learning exercise in:
- low-level socket programming
- TCP client-server architecture
- concurrent client handling with a thread pool
- command execution and process I/O
- platform differences between Linux and Windows sockets
- security tradeoffs in remote execution systems

---

For deeper study, you can extend the project by:
- adding TLS support
- using a proper command framing protocol
- implementing a secure command whitelist
- adding a server-side session timeout
- improving authentication with hashed passwords or OAuth-like tokens
