# Experiment 07: DNS and HTTPS Packet Analysis Using Wireshark

## 1. Experiment Title
Packet Sniffing and Protocol Analysis of DNS and HTTP/HTTPS (TLS) Traffic Using Wireshark.

---

## 2. Aim
To study and analyze the packet encapsulation structure of the Domain Name System (DNS) and evaluate the security architecture of plaintext HTTP versus encrypted HTTPS (TLS) using network protocol dissection across the OSI and TCP/IP stack.

---

## 3. Theory / Introduction
Wireshark is a packet analyzer that captures network frames directly from a Network Interface Card (NIC) via the Npcap or libpcap library, decoding raw bitstreams into protocol hierarchies.

### 3.1 Encapsulation Hierarchy (OSI Stack Representation)

```
 +-------------------------------------------------------------------------+
 | Layer 2: Data Link | Ethernet II (Source MAC -> Destination MAC)         |
 +--------------------+----------------------------------------------------+
 | Layer 3: Network   | IPv4 (Source IP -> Destination IP, Protocol: UDP/TCP) |
 +--------------------+----------------------------------------------------+
 | Layer 4: Transport | UDP (Port 53 for DNS) OR TCP (Port 80/443)         |
 +--------------------+----------------------------------------------------+
 | Layer 7: App Layer | DNS / HTTP / TLS (Encrypted Application Data)      |
 +-------------------------------------------------------------------------+
```

### 3.2 DNS Packet Architecture
DNS messages are exchanged over UDP port `53`. The packet format contains:
- **Transaction ID (16 bits):** A random identifier assigned by the client to correlate query and response packets.
- **Flags (16 bits):**
  - `QR (Query/Response)`: 0 = Query, 1 = Response.
  - `Opcode`: 0 = Standard Query.
  - `AA (Authoritative Answer)`: Indicates if the responding server is authoritative.
  - `TC (Truncated)`: Indicates if message exceeds 512 bytes.
  - `RD (Recursion Desired)`: Set by client requesting recursive resolution.
  - `RA (Recursion Available)`: Set by server indicating recursive queries are supported.
  - `RCODE (Reply Code)`: 0 = No Error, 3 = Non-Existent Domain (NXDomain).
- **Questions:** Count and list of domain queries (Name, Type, Class).
- **Answers:** Count and resource records (Name, Type, TTL, IP Address).

```
 +------------------------------------------------------------------+
 |                       DNS Header Structure                       |
 +--------------------------------+---------------------------------+
 |      Transaction ID (16)       |          Flags (16)             |
 +--------------------------------+---------------------------------+
 |      Questions Count (16)      |        Answer RRs Count (16)    |
 +--------------------------------+---------------------------------+
 |     Authority RRs Count (16)   |      Additional RRs Count (16)  |
 +--------------------------------+---------------------------------+
 |                   Queries / Answers Payload                      |
 +------------------------------------------------------------------+
```

### 3.3 HTTP vs. HTTPS / TLS Analysis
- **HTTP (Hypertext Transfer Protocol - TCP Port 80):** Transmits data entirely in unencrypted plaintext. Headers, status codes, and message payloads are transmitted in the clear.
- **HTTPS (HTTP Secure - TCP Port 443):** Wraps HTTP inside a Transport Layer Security (TLS) tunnel. The client and server perform a cryptographic handshake to authenticate the server (via X.509 certificates) and negotiate symmetric encryption keys (AES-GCM / ChaCha20-Poly1305). Once the handshake completes, all application data is encrypted.
- **Wireshark Display Filter Syntax:**
  - Filtering by `http` isolates unencrypted web traffic on port 80.
  - Typing `https` directly into the Wireshark filter bar produces a syntax error (`"https" is not a valid protocol or protocol field`). In Wireshark, secure traffic is filtered using `tls`, `ssl`, or `tcp.port == 443`.
  - Without the client's session keys, TLS Application Data cannot be read.

---

## 4. Objectives
1. Understand packet encapsulation across Ethernet, IPv4, UDP, and TCP layers.
2. Examine DNS query and response transactions, transaction IDs, and header flags.
3. Compare the security posture of unencrypted HTTP against encrypted TLS sessions.
4. Understand protocol dissector filter syntax in network analyzers.

---

## 5. Required Software and Tools
- **Software:** Wireshark Network Protocol Analyzer with Npcap/libpcap packet capture driver.
- **Diagnostic Utilities:** `nslookup`, standard web browser, or command-line HTTP clients.

---

## 6. Comparative Analysis: HTTP vs HTTPS (TLS)

| Parameter | HTTP (Plaintext Web Traffic) | HTTPS / TLS (Encrypted Web Traffic) |
|---|---|---|
| **Standard Port** | Port 80 | Port 443 |
| **Wireshark Filter** | `http` | `tls` or `tcp.port == 443` (`https` is invalid) |
| **Confidentiality** | None; headers, URLs, and payloads visible in clear text | Fully encrypted using symmetric cipher (AES / ChaCha20) |
| **Integrity** | Vulnerable to packet tampering and injection | Cryptographic HMAC / AEAD tags prevent unauthorized modification |
| **Authentication** | None | Server identity authenticated via digital X.509 certificate |
| **Packet Visibility** | Headers, requests, and response payloads fully readable | Only TLS handshake metadata (SNI, Cipher suites) visible; payload is opaque |

---

## 7. Result / Conclusion
Network packet encapsulation and transport behaviors were analyzed. The dissection confirmed the hierarchical encapsulation of Ethernet, IPv4, UDP, and TCP protocols. DNS query and response formats were verified via transaction IDs and status flags, and the clear-text vulnerabilities of HTTP were contrasted with the encryption safeguards provided by HTTPS/TLS.
