# Experiment 02: TCP Server Socket Programming

## 1. Experiment Title
Implementation of a Connection-Oriented TCP Server Using Berkeley Sockets in C.

---

## 2. Aim
To design, implement, and analyze a connection-oriented TCP server in C using the POSIX socket API. The server creates a stream socket, binds to port `8080`, listens for incoming connection requests, accepts an incoming connection from a TCP client, receives data, sends a reply, and terminates the session cleanly.

---

## 3. Theory / Introduction
The Transmission Control Protocol (TCP) is a core transport-layer protocol providing reliable, ordered, error-checked, and stream-oriented delivery of octets between networked applications.

### 3.1 Key Characteristics of TCP
- **Connection-Oriented:** A dedicated logical connection is established via a three-way handshake ($SYN \rightarrow SYN+ACK \rightarrow ACK$) before any user payload is transmitted.
- **Reliability:** Employs sequence numbers, cumulative acknowledgements (ACK), and retransmission timers to guarantee data delivery without loss or duplication.
- **Flow Control:** Implements a sliding window mechanism where the receiver advertises its available buffer capacity in the window field.
- **Congestion Control:** Regulates injection rate into the network using slow start, congestion avoidance, fast retransmit, and fast recovery algorithms.

### 3.2 TCP Server Socket Lifecycle

```
        socket()           --> Create endpoint (AF_INET, SOCK_STREAM)
           |
       setsockopt()        --> Enable SO_REUSEADDR / SO_REUSEPORT
           |
         bind()            --> Bind to IP (INADDR_ANY) and Port (8080)
           |
        listen()           --> Enter passive listening state with backlog
           |
        accept()           --> Blocks until incoming SYN arrives; creates new socket FD
           |
         read()            --> Receives data sent by client
           |
         send()            --> Transmits response data to client
           |
         close()           --> Closes connection and sends FIN packet
```

### 3.3 Core System Calls Used
- `socket(int domain, int type, int protocol)`: Allocates a socket descriptor. Domain `AF_INET` designates IPv4; `SOCK_STREAM` specifies a reliable two-way connected byte stream (TCP).
- `setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)`: Sets socket options. Setting `SO_REUSEADDR` allows the local address to be reused immediately without waiting for the `TIME_WAIT` socket state to expire.
- `bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)`: Associates the socket descriptor with a specific local IP address and port number.
- `listen(int sockfd, int backlog)`: Marks the socket as passive to accept incoming connections. The `backlog` argument sets the maximum length of the queue of pending connections.
- `accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)`: Extracts the first connection request on the queue of pending connections for the listening socket, creates a new connected socket descriptor, and returns it.
- `read()` / `send()`: Performs input/output over the established stream.

---

## 4. Objectives
1. Understand the socket programming abstraction in UNIX/Linux environments.
2. Master the sequential workflow of server-side TCP socket system calls.
3. Observe port binding, passive socket listening, and client connection acceptance.
4. Verify end-to-end data transfer between separate client and server processes.

---

## 5. Required Software and Tools
- **Operating System:** Linux (Ubuntu 20.04/22.04/24.04), WSL (Windows Subsystem for Linux), or any POSIX-compliant UNIX environment.
- **Compiler:** GCC (GNU Compiler Collection).
- **Text Editor / IDE:** Gedit, Nano, Vim, or Visual Studio Code.
- **Terminal:** Bash / GNOME Terminal / Windows Terminal.

---

## 6. Algorithm / Working Principle
1. Start the program.
2. Create an IPv4 TCP stream socket using `socket(AF_INET, SOCK_STREAM, 0)`.
3. If socket creation fails, print an error using `perror()` and terminate.
4. Set `SO_REUSEADDR` and `SO_REUSEPORT` socket options to enable rapid port re-binding.
5. Populate the `sockaddr_in` structure:
   - Set `sin_family = AF_INET`.
   - Set `sin_addr.s_addr = INADDR_ANY` (accept connections on all local interfaces).
   - Set `sin_port = htons(PORT)` (convert host port 8080 to network byte order).
6. Bind the socket using `bind()`.
7. Put the socket in listening mode with a backlog queue of 3 using `listen()`.
8. Block and wait for an incoming connection from a client using `accept()`.
9. Upon connection, retrieve the client's socket descriptor and address parameters.
10. Read the client's message using `read()` into a buffer and display it on the terminal.
11. Send a response string (`"Hello from server"`) back to the client using `send()`.
12. Display the client's ephemeral port number (`ntohs(address.sin_port)`).
13. Close the connected socket and the master listening socket.
14. End the program.

---

## 7. Result / Conclusion
A connection-oriented TCP server was successfully implemented in C using POSIX stream sockets. The program demonstrated reliable socket creation, port binding, passive connection listening, client acceptance, bidirectional data exchange, and graceful socket shutdown.
