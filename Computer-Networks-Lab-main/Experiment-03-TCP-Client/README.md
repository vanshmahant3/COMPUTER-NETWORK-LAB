# Experiment 03: TCP Client Socket Programming

## 1. Experiment Title
Implementation of a Connection-Oriented TCP Client Using Berkeley Sockets in C.

---

## 2. Aim
To design, implement, and analyze an active TCP client program in C using POSIX stream sockets. The client establishes a connection with the TCP server listening on loopback IP `127.0.0.1` and port `8080`, transmits a client greeting message (`"HELLO from CLIENT"`), receives the server's response (`"Hello from server"`), and terminates the connection cleanly.

---

## 3. Theory / Introduction
While a TCP server performs a **passive open** by binding to a port and waiting for incoming requests, a TCP client initiates an **active open** by requesting a connection to a specific remote server IP address and port number.

### 3.1 TCP Client Socket Lifecycle

```
        socket()           --> Create endpoint (AF_INET, SOCK_STREAM)
           |
       inet_pton()         --> Convert "127.0.0.1" from text to binary network format
           |
        connect()          --> Initiates 3-way handshake (SYN) to Server (127.0.0.1:8080)
           |
         send()            --> Transmits payload ("HELLO from CLIENT")
           |
         read()            --> Awaits and receives response from server
           |
         close()           --> Sends FIN segment and terminates connection
```

### 3.2 Key System Calls and Functions
- `socket(AF_INET, SOCK_STREAM, 0)`: Allocates an active stream socket descriptor for IPv4 communication.
- `inet_pton(int af, const char *src, void *dst)`: "Internet Presentation to Numeric" converts a human-readable IPv4 dotted-decimal string (such as `"127.0.0.1"`) into binary form in network byte order stored in `in_addr`.
- `connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)`: Connects the socket referred to by `sockfd` to the address specified by `addr`. This triggers the kernel to:
  1. Assign an unused ephemeral port from the local operating system range.
  2. Initiate the TCP three-way handshake by transmitting a SYN segment.
  3. Block until the SYN+ACK arrives from the server and the ACK is transmitted, placing the socket into the `ESTABLISHED` state.
- `send()` and `read()`: Transmit and receive payloads through the established full-duplex byte stream.
- `close()`: Releases the socket descriptor and triggers the four-way connection teardown sequence ($FIN \rightarrow ACK \rightarrow FIN \rightarrow ACK$).

---

## 4. Objectives
1. Understand the client-side socket creation and connection lifecycle.
2. Differentiate between active open (client) and passive open (server).
3. Verify IPv4 address conversion using `inet_pton()`.
4. Observe proper error handling when the target server is unreachable (`Connection Failed`).

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
3. If socket creation returns a negative value, print an error and terminate.
4. Initialize the `sockaddr_in serv_addr` structure:
   - Set address family `sin_family = AF_INET`.
   - Set destination port `sin_port = htons(PORT)`.
5. Convert the destination IP string (`"127.0.0.1"`) to binary using `inet_pton()`. If invalid or unsupported, print an error and terminate.
6. Initiate a connection to the server using `connect()`.
   - If the server is offline or unreachable, `connect()` returns `-1`, prints `"Connection Failed"`, and exits.
7. Upon successful connection establishment, transmit the message `"HELLO from CLIENT"` using `send()`.
8. Print confirmation: `"Hello message sent"`.
9. Block and read the incoming response from the server using `read()`.
10. Null-terminate the received buffer and print the message to standard output.
11. Close the socket descriptor using `close()`.
12. End the program.

---

## 7. Result / Conclusion
A connection-oriented TCP client was successfully implemented in C using POSIX stream sockets. The client demonstrated proper address conversion, active connection initiation via three-way handshake, payload transmission, synchronized response reception, and clean disconnection.
