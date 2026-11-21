# Experiment 10: Distance Vector Algorithm

## 1. Experiment Title
Implementation of the Distance Vector Routing (DVR) Algorithm in C.

---

## 2. Aim
To design, implement, and analyze the Distance Vector Routing (DVR) algorithm in C based on the distributed Bellman-Ford algorithm. The program accepts an adjacency cost matrix for an arbitrary network graph, computes the shortest path between every pair of nodes, tracks the next-hop router for forwarding, and outputs the converged routing tables.

---

## 3. Theory / Introduction
Routing is the process by which intermediate network devices (routers) determine the optimal end-to-end path for forwarding packets from a source to a destination.

### 3.1 Routing Protocol Classifications
- **Distance Vector Protocols (e.g., Routing Information Protocol - RIP):** Each router maintains a vector of distances to every known destination and periodically shares this vector only with its directly connected immediate neighbors.
- **Link State Protocols (e.g., Open Shortest Path First - OSPF):** Each router broadcasts the status of its direct links to all routers in the entire routing area (using Dijkstra's algorithm to compute paths).

### 3.2 The Bellman-Ford Equation
Distance Vector routing relies on the Bellman-Ford dynamic programming principle:

$$D_x(y) = \min_{v \in \text{Neighbors}(x)} \{ c(x, v) + D_v(y) \}$$

Where:
- $D_x(y)$: The calculated minimum distance from node $x$ to destination node $y$.
- $c(x, v)$: The direct link cost between node $x$ and its immediate neighbor $v$.
- $D_v(y)$: The current shortest distance from neighbor $v$ to destination node $y$.

```
               (2)
        [0] ---------- [1]
         |              |
     (1) |              | (3)
         |              |
        [3] ---------- [2]
               (4)
```

### 3.3 Convergence and Routing Table Updates
1. **Initialization:** Every node initializes its distance table with direct link costs from its interface configurations. Destinations with no direct link are assigned a cost of infinity (`INF = 999`), and the next hop is set to `-1`.
2. **Iteration / Relaxation:** For each iteration (up to $N - 1$ rounds for a graph with $N$ vertices), each node inspects all neighbors $k$. If routing through neighbor $k$ yields a shorter path to destination $j$ ($c[i][k] + rt[k].dist[j] < rt[i].dist[j]$), the node updates its distance and sets `from[j] = k`.
3. **Early Termination:** If a complete round passes without any table updates (`updated == 0`), the network has converged, and the algorithm halts early.

---

## 4. Objectives
1. Implement the Bellman-Ford relaxation equation for network routing.
2. Construct and update dynamic routing tables containing Destination, Next Hop, and Metric Distance.
3. Observe iterative route convergence across an arbitrary network topology.
4. Analyze the count-to-infinity problem and routing loop prevention techniques.

---

## 5. Required Software and Tools
- **Language:** C (Standard C99/C11).
- **Compiler:** GCC (GNU Compiler Collection).
- **Platforms:** Linux, WSL, macOS, Windows, or Online C Compilers.

---

## 6. Algorithm / Working Principle
1. Start the program.
2. Read the total number of network nodes (`nodes`).
3. Read the $N \times N$ link cost matrix `cost[i][j]`. A value of `999` denotes infinity (no direct link).
4. Initialize the routing table for every node $i$:
   - Set `cost[i][i] = 0`.
   - For all destinations $j$:
     - `rt[i].dist[j] = cost[i][j]`.
     - If `cost[i][j] < INF` and `i != j`, set `rt[i].from[j] = j` (direct connection).
     - Else, set `rt[i].from[j] = -1`.
5. Perform Bellman-Ford iterations for `iteration = 0` to `nodes - 2`:
   - Set flag `updated = 0`.
   - For each node $i$:
     - For each destination $j$:
       - For each neighbor $k$:
         - If `cost[i][k] >= INF` or `rt[k].dist[j] >= INF`, skip.
         - Calculate `newdist = cost[i][k] + rt[k].dist[j]`.
         - If `newdist < rt[i].dist[j]`:
           - Update distance: `rt[i].dist[j] = newdist`.
           - Update next hop: `rt[i].from[j] = k`.
           - Set `updated = 1`.
   - If `!updated`, break early (convergence achieved).
6. Print the converged routing table for every node, listing Destination, Next Hop, and Distance.
7. End the program.

---

## 7. Result / Conclusion
The Distance Vector Routing algorithm was successfully implemented in C using the Bellman-Ford algorithm. The simulation verified autonomous distributed path discovery, routing table convergence, next-hop recording, and shortest path calculation across all network nodes.
