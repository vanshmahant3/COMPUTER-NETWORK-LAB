# Experiment 05: UDP Client Socket Programming

## 1. Experiment Title
Implementation of a Connectionless UDP Client Using Datagram Sockets in C.

---

## 2. Aim
To design, implement, and evaluate an interactive UDP client in C using POSIX datagram sockets (`SOCK_DGRAM`). The client transmits user-defined text messages to the UDP server listening on `127.0.0.1:10004` using `sendto()`, receives the echoed payload via `recvfrom()`, and displays the response on the terminal.

---

## 3. Theory / Introduction
In UDP communication, the client does not establish a persistent virtual circuit with the server. Instead, it directly encapsulates each data payload into an independent datagram with the destination IP address and port number embedded in the transport header.

### 3.1 UDP Client Socket Lifecycle

```
        socket()           --> Create datagram socket (AF_INET, SOCK_DGRAM)
           |
     +-----> fgets()       --> Read interactive message string from user input
     |         |
     |      sendto()      --> Transmits datagram to target Server (127.0.0.1:10004)
     |         |
     |      recvfrom()    --> Waits for and receives echoed datagram
     |         |
     |      printf()      --> Displays echoed message on console
     |         |
     +---------+           --> Continues until user terminates
           |
         close()           --> Releases socket descriptor
```

### 3.2 Contrast: TCP Client vs. UDP Client

| Architectural Feature | TCP Client (Exp 03) | UDP Client (Exp 05) |
|---|---|---|
| **Connection Setup** | Three-way handshake (`connect()` required) | None (`connect()` is optional) |
| **Transmission Call** | `send()` / `write()` | `sendto()` with destination address |
| **Reception Call** | `read()` / `recv()` | `recvfrom()` with address capture |
| **Data Boundary** | Continuous byte stream (no boundaries) | Preserved message/datagram boundaries |
| **State Tracking** | Connection state maintained by kernel | Stateless; each datagram is independent |
| **Server Offline Error** | `connect()` returns `Connection Failed` | `sendto()` succeeds (packet dropped silently by OS/network) |

---

## 4. Objectives
1. Understand the operational mechanics of connectionless UDP client communication.
2. Implement message framing and socket transmission using `sendto()`.
3. Receive echoed server packets using `recvfrom()` without a prior connection establishment.
4. Observe the lack of connection state and immediate datagram transmission.

---

## 5. Required Software and Tools
- **Operating System:** Linux (Ubuntu 20.04/22.04/24.04), WSL (Windows Subsystem for Linux), or any POSIX-compliant UNIX environment.
- **Compiler:** GCC (GNU Compiler Collection).
- **Text Editor / IDE:** Gedit, Nano, Vim, or Visual Studio Code.
- **Terminal:** Bash / GNOME Terminal / Windows Terminal.

---

## 6. Algorithm / Working Principle
1. Start the program.
2. Instantiate a UDP datagram socket using `socket(AF_INET, SOCK_DGRAM, 0)`.
3. If socket creation returns a negative value, display an error and terminate.
4. Set up the destination server address structure (`sockaddr_in server_addr`):
   - Set `sin_family = AF_INET`.
   - Set `sin_port = htons(PORT)` (`10004`).
   - Convert string IP address `"127.0.0.1"` into numeric format using `inet_addr()`.
5. Enter a loop:
   - Read input line into `buffer` using `fgets()`.
   - Send the message datagram to the server using `sendto()`.
   - Clear the reception buffer with `memset()`.
   - Receive the echoed response datagram from the server using `recvfrom()`.
   - Null-terminate the received buffer and print response.
6. Close the socket using `close()`.
7. End the program.

---

## 7. Result / Conclusion
An interactive UDP client was successfully implemented in C using POSIX datagram sockets. The experiment demonstrated connectionless socket creation, packet encapsulation, datagram transmission using `sendto()`, and response reception using `recvfrom()`.
