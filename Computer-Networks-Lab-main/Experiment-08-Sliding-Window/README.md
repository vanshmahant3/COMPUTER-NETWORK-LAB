# Experiment 08: Sliding Window Protocol

## 1. Experiment Title
Simulation of the Sliding Window Flow Control Protocol in C.

---

## 2. Aim
To design, implement, and simulate the Sliding Window (Go-Back-N) protocol in C. The program simulates sender window management, frame transmission within the permissible window size, cumulative acknowledgment reception, window advancement upon successful ACKs, and window rollback upon transmission errors.

---

## 3. Theory / Introduction
In computer networks, flow control prevents a fast sender from overwhelming a slow receiver with data. Unrestricted transmission on unreliable physical links leads to buffer overflows, packet loss, and network congestion.

### 3.1 Flow Control Protocols
- **Stop-and-Wait ARQ:** The sender transmits one frame and waits for an acknowledgment (ACK) before transmitting the next. Under high propagation delay, channel utilization is low.
- **Sliding Window Protocols:** Allow the sender to transmit multiple consecutive frames before waiting for an ACK (pipelining). The maximum number of unacknowledged frames in transit is bounded by the **Window Size ($N$)**.

### 3.2 Sliding Window Working Mechanism (Go-Back-N Principle)

```
 Frame Sequence:   1   2   3   4   5   6   7   8   9   10
                 +-------+
 Initial Window: | 1   2 |  (Window Size = 2)
                 +-------+
                  --> Send Frame 1, Frame 2
                  <-- Receive ACK for Frame 1
                     +-------+
  Window Slides:     | 2   3 |
                     +-------+
                  --> Send Frame 2, Frame 3
                  <-- Error on Frame 2 ACK
                     (Window rolls back: Retransmit Frame 2)
```

1. **Sender Window ($W_s$):** Defines the range of consecutive sequence numbers the sender is permitted to transmit without receiving an ACK.
2. **Window Sliding:** When the sender receives an acknowledgment for frame $k$ such that $k > \text{current}$, the base of the window slides forward to $k$, allowing new frames to be transmitted.
3. **Error Handling (Go-Back-N):** If an acknowledgment fails or reports an unacknowledged frame, the sender retreats to the earliest unacknowledged frame (`current + 1`) and retransmits all frames within the current window.

---

## 4. Objectives
1. Understand the concept of pipelined data transmission and link utilization.
2. Implement dynamic window boundaries (`current` to `current + window_size`).
3. Model positive acknowledgment reception and window advancement.
4. Simulate retransmission upon corrupted or lost acknowledgments.

---

## 5. Required Software and Tools
- **Language:** C (Standard C99 or C11).
- **Compiler:** GCC (GNU Compiler Collection) or Clang.
- **Platforms:** Linux, WSL, macOS, Windows (GCC/MinGW), or Online C Compilers.

---

## 6. Algorithm / Working Principle
1. Start the program.
2. Read the total number of frames (`total_frames`) to transmit.
3. Read the sender window size (`window_size`).
4. Initialize `current = 0` (representing the base of unacknowledged frames).
5. While `current < total_frames`:
   - Transmit all frames within the current window from `i = 0` up to `window_size - 1`, provided `(current + i) < total_frames`.
   - Prompt the user to enter the last successful frame number acknowledged (`ack`).
   - If `ack > current` and `ack <= total_frames`:
     - Advance window base: `current = ack`.
   - Else:
     - Print error referencing `current + 1`.
     - The window does not slide; transmission repeats from `current + 1`.
6. When `current >= total_frames`, print completion status.
7. End the program.

---

## 7. Result / Conclusion
The Sliding Window protocol was simulated in C. The experiment demonstrated pipelined transmission of multiple frames within the specified window, cumulative acknowledgment processing, window sliding, and retransmission recovery upon simulated channel errors.
