# Experiment 04: UDP Server Socket Programming

## 1. Experiment Title
Implementation of a Connectionless UDP Echo Server Using Datagram Sockets in C.

---

## 2. Aim
To design, implement, and analyze a connectionless UDP server in C using POSIX datagram sockets (`SOCK_DGRAM`). The server binds to port `10004`, listens for incoming datagrams from clients using `recvfrom()`, displays the received messages on the console, and echoes each message back to the sender's address using `sendto()`.

---

## 3. Theory / Introduction
The User Datagram Protocol (UDP) is an un-sequenced, connectionless transport protocol defined in RFC 768. Unlike TCP, UDP transmits independent packets called **datagrams** without establishing an initial end-to-end connection.

### 3.1 Key Characteristics of UDP
- **Connectionless:** No handshake (no SYN/ACK exchange) occurs before data transmission. Datagrams are transmitted immediately.
- **Message-Oriented (Preserves Message Boundaries):** Each `sendto()` call generates a distinct datagram. Each `recvfrom()` call reads exactly one datagram. Unlike TCP byte streams, packets do not merge or split.
- **Unreliable Delivery:** UDP provides best-effort delivery. Packets may be lost, duplicated, delayed, or arrive out of order without retransmission or error notification from the transport layer.
- **Minimal Overhead:** The UDP header is fixed at only 8 bytes (Source Port, Destination Port, Length, Checksum), compared to TCP's 20–60 byte header, making UDP ideal for low-latency and real-time streaming applications (DNS, DHCP, VoIP, video conferencing).

### 3.2 UDP Server Socket Lifecycle

```
        socket()           --> Create datagram socket (AF_INET, SOCK_DGRAM)
           |
         bind()            --> Bind to IP (INADDR_ANY) and Port (10004)
           |
     +-----> recvfrom()    --> Blocks waiting for datagram; captures client IP & port
     |         |
     |      sendto()      --> Transmits echo datagram back to client address
     |         |
     +---------+           --> Loops to handle further datagrams
```

*Note: UDP servers do NOT call `listen()` or `accept()`. There is no persistent connection or dedicated child socket descriptor; all communication passes through the single bound datagram socket descriptor.*

---

## 4. Objectives
1. Understand the architecture and behavior of connectionless datagram sockets.
2. Implement server-side UDP socket initialization, port binding, and packet reception.
3. Utilize `recvfrom()` and `sendto()` to capture client socket addresses dynamically.
4. Contrast the architectural and performance trade-offs between UDP and TCP.

---

## 5. Required Software and Tools
- **Operating System:** Linux (Ubuntu 20.04/22.04/24.04), WSL (Windows Subsystem for Linux), or any POSIX-compliant UNIX environment.
- **Compiler:** GCC (GNU Compiler Collection).
- **Text Editor / IDE:** Gedit, Nano, Vim, or Visual Studio Code.
- **Terminal:** Bash / GNOME Terminal / Windows Terminal.

---

## 6. Algorithm / Working Principle
1. Start the program.
2. Create an IPv4 UDP datagram socket using `socket(AF_INET, SOCK_DGRAM, 0)`.
3. If socket creation returns a negative integer, display an error and exit.
4. Initialize the server address structure (`sockaddr_in`):
   - Set address family to `AF_INET`.
   - Set IP address to `INADDR_ANY` (accept datagrams across all local interfaces).
   - Set port to `htons(PORT)` (`10004`).
5. Bind the socket to the port using `bind()`.
6. Print server status: `"UDP Echo Server listening on port 10004..."`.
7. Enter a `while (1)` loop:
   - Clear the reception buffer using `memset()`.
   - Invoke `recvfrom()` to wait for and read an incoming datagram while capturing the client's socket address (`client_addr`) and address length (`addrlen`).
   - If received bytes $\le 0$, continue.
   - Display the received text string on standard output: `"Received: %s"`.
   - Echo the identical buffer back to the sender using `sendto()` using the captured `client_addr`.
8. Close the socket upon shutdown.
9. End the program.

---

## 7. Result / Conclusion
A connectionless UDP echo server was successfully implemented in C using POSIX datagram sockets. The server demonstrated successful binding to port 10004, datagram packet reception via `recvfrom()`, message parsing, and echo reflection via `sendto()`.
