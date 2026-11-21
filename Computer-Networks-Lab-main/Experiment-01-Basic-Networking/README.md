# Experiment 01: Basic Networking Elements and Devices

## 1. Experiment Title
Study of Basic Networking Elements, Transmission Media, and Connecting Devices.

---

## 2. Aim
To study and understand the fundamental building blocks of computer networks, including network architectures, transmission media, and the functionality, operational layers, and practical differences among essential networking devices such as Hubs, Switches, Routers, Bridges, Repeaters, Gateways, Modems, and Network Interface Cards (NICs).

---

## 3. Theory / Introduction
A computer network is an interconnected collection of autonomous computing devices capable of exchanging data and sharing resources through transmission media and standard communication protocols. Network devices operate at distinct layers of the Open Systems Interconnection (OSI) reference model and TCP/IP stack to manage signal regeneration, frame filtering, packet forwarding, routing, and protocol conversion.

### 3.1 Network Classification and Topologies
- **Local Area Network (LAN):** Confined to a localized geographical area (e.g., laboratory, office building). Operates typically over Ethernet or Wi-Fi with high data transfer rates and low latency.
- **Metropolitan Area Network (MAN):** Covers a city or campus-wide region (e.g., cable television network, municipal network).
- **Wide Area Network (WAN):** Spans large geographical regions, countries, or continents (e.g., the Internet), connecting multiple LANs via routers and telecommunication links.

Key topologies include **Bus**, **Star**, **Ring**, **Mesh**, and **Hybrid**. Modern enterprise and campus Ethernet networks predominantly employ an extended star topology with centralized switches.

### 3.2 Network Connecting Devices

```
 +-------------------------------------------------------------------------+
 |                            OSI REFERENCE MODEL                          |
 +-------------------+-------------------------+---------------------------+
 | Layer 7: Application | Gateway                 | Protocol conversion       |
 | Layer 6: Presentation| Gateway                 | Data syntax/encryption    |
 | Layer 5: Session     | Gateway                 | Session management        |
 | Layer 4: Transport   | Gateway, L4 Switch      | End-to-end transport      |
 | Layer 3: Network     | Router, Layer 3 Switch  | Logical addressing (IP)   |
 | Layer 2: Data Link   | Switch, Bridge, NIC     | Physical addressing (MAC) |
 | Layer 1: Physical    | Hub, Repeater, Modem    | Bits, electrical signals  |
 +-------------------+-------------------------+---------------------------+
```

#### 1. Repeater (OSI Layer 1 - Physical)
- **Function:** Receives incoming electrical, optical, or wireless signals attenuated due to cable length transmission losses, regenerates (amplifies and retimes) the clean signal at full strength, and retransmits it.
- **Characteristics:** Does not inspect MAC addresses or IP packets. Operates purely at the bit level. It does not divide collision domains or broadcast domains.

#### 2. Hub (OSI Layer 1 - Physical)
- **Function:** A multi-port repeater used as a central connection point in traditional star topologies.
- **Working Mechanism:** When a frame arrives at one port, the electrical signal is regenerated and flooded out of all other ports, regardless of the intended destination.
- **Limitation:** All connected hosts share a single collision domain and a single broadcast domain, leading to high collision probabilities under load and half-duplex operation.

#### 3. Bridge (OSI Layer 2 - Data Link)
- **Function:** Connects two separate physical LAN segments and filters traffic based on Media Access Control (MAC) addresses.
- **Working Mechanism:** Reads incoming frames, learns source MAC addresses dynamically, and populates its Forwarding Information Base (FIB). If the destination MAC is on the same segment, the frame is filtered; if on the other segment, it is forwarded.
- **Significance:** Divides one large collision domain into two smaller collision domains while keeping a single broadcast domain.

#### 4. Switch (OSI Layer 2 - Data Link / Layer 3 - Network)
- **Function:** A high-speed multi-port bridge that connects multiple end systems in a local network.
- **Working Mechanism:** Inspects incoming Ethernet frames, maps the source MAC address to the ingress physical port in its MAC Address Table (CAM table), and forwards unicast frames strictly to the designated destination port.
- **Collision & Broadcast Domains:** Every individual switch port constitutes its own isolated collision domain (full-duplex transmission). All ports default to a single broadcast domain unless segmented using Virtual LANs (VLANs).
- **Layer 3 Switch:** Integrates hardware-based ASIC packet forwarding to route IP packets between VLANs at wire speed.

#### 5. Router (OSI Layer 3 - Network)
- **Function:** Interconnects heterogeneous networks and determines the optimal path for forwarding IP packets toward their destination.
- **Working Mechanism:** Maintains routing tables populated via static routes or dynamic routing protocols (e.g., RIP, OSPF, BGP). Strips Layer 2 framing, examines the destination Layer 3 IP address, determines the next-hop interface, encapsulates the packet in a new Layer 2 frame appropriate for the outbound link, and transmits it.
- **Significance:** Limits and terminates broadcast domains (routers do not forward broadcast packets by default) and isolates collision domains.

#### 6. Gateway (OSI Layers 4 through 7)
- **Function:** A network node that acts as an entrance to another network, performing protocol translation between fundamentally incompatible network architectures, protocol stacks, or data formats.

#### 7. Modem (Modulator - Demodulator)
- **Function:** Converts digital data from a computer into analog signals suitable for transmission over analog communication media (e.g., telephone lines, coaxial cable), and demodulates incoming analog signals back into digital bitstreams.

#### 8. Network Interface Card (NIC)
- **Function:** Hardware component providing the physical and data link connection between a host computer and the network medium.
- **Characteristics:** Contains a unique 48-bit burned-in physical MAC address, implements CSMA/CD or full-duplex Ethernet protocols, and manages serialization/deserialization of frames.

---

## 4. Objectives
1. Identify and categorize common networking elements according to their respective OSI reference model layers.
2. Differentiate between collision domains and broadcast domains across hubs, switches, and routers.
3. Understand the role of physical (MAC) addressing versus logical (IP) addressing in network forwarding.
4. Analyze how routers connect distinct networks and isolate broadcast traffic.

---

## 5. Required Software and Tools
- Network topology visualization or simulation tools (Packet Tracer, GNS3, or Wireshark).
- Command-line diagnostic utilities (`ipconfig` / `ifconfig`, `arp -a`, `route print`).

---

## 6. Device Comparison Matrix

| Device | Primary OSI Layer | Operating Address | Collision Domains | Broadcast Domains | Forwarding Mechanism | Duplex Mode |
|---|---|---|---|---|---|---|
| **Repeater** | Layer 1 (Physical) | None (bits) | 1 shared | 1 shared | Signal regeneration | Half-duplex |
| **Hub** | Layer 1 (Physical) | None (bits) | 1 shared across all ports | 1 shared across all ports | Flooding (broadcast to all ports) | Half-duplex |
| **Bridge** | Layer 2 (Data Link) | MAC Address | 1 per segment (typically 2) | 1 shared | Software filtering / forwarding | Half/Full duplex |
| **Switch** | Layer 2 (Data Link) | MAC Address | 1 per port (microsegmentation) | 1 shared (divided by VLANs) | Hardware ASIC table lookup | Full-duplex |
| **Router** | Layer 3 (Network) | IP Address | 1 per interface | 1 per interface (blocks broadcasts) | Routing table lookup | Full-duplex |
| **Gateway** | Layers 4 – 7 | Port / Application Data | N/A | Dependent on underlying link | Protocol translation & conversion | Full-duplex |
| **Modem** | Layer 1 (Physical) | None | N/A | N/A | Modulation / Demodulation | Full/Half duplex |

---

## 7. Working Principles & Network Architecture

### 7.1 Collision Domain vs. Broadcast Domain
- **Collision Domain:** A network segment where data packets can collide with one another when sent simultaneously on a shared medium.
  - A Hub has **1** collision domain for all ports.
  - A Switch creates **N** separate collision domains for $N$ ports.
  - A Router creates **1** collision domain per physical interface.
- **Broadcast Domain:** A network segment containing all devices that receive a broadcast frame originating from any node within that segment.
  - Hubs and Switches belong to **1** broadcast domain by default.
  - Routers **break** broadcast domains; each router interface defines a separate broadcast domain.

```
       [ Host A ]        [ Host B ]
            \                /
             \              /
         +-----------------------+
         |    Layer 2 Switch     |  <-- N Collision Domains (1 per port)
         +-----------------------+      1 Single Broadcast Domain
                     |
                     | (LAN 1)
             +---------------+
             | Layer 3 Router|  <-- Separates Broadcast Domains
             +---------------+
                     | (LAN 2)
                     |
         +-----------------------+
         |    Layer 2 Switch     |
         +-----------------------+
            /                \
           /                  \
      [ Host C ]          [ Host D ]
```

---

## 8. Result / Conclusion
The characteristics, operational layers, and architectural differences of primary computer networking elements were thoroughly studied. The distinction between physical (Layer 1), data link (Layer 2), and network (Layer 3) devices was established, confirming how switches eliminate packet collisions via port isolation and routers segment broadcast domains to facilitate internetwork communication.
