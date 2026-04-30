#include <iostream>
#include "algorithms.h"

// Dijkstra's Algorithm - Shortest Path Algorithm

std::vector<int> dijkstra(const std::vector<std::vector<std::pair<int, int>>> &adj, const int src)
{
    // Min-heap (priority queue) storing distance and node
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    const int nodeCount = adj.size();
    std::vector<int> dist(nodeCount, INT_MAX);

    // Distance from source to itself is 0
    dist[src] = 0;
    pq.emplace(0, src); // pair = {distance, node}

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        // skip distance that not shortest latest one
        if (d > dist[u])
            continue;

        // explore all neighbours of current node
        // nv = neighbour vertex, nvd = neighbour vertex distance
        for (auto &[nv, nvd] : adj[u])
        {
            // if found a shorter path to nv through u, update it
            if (dist[u] + nvd < dist[nv])
            {
                dist[nv] = dist[u] + nvd;
                pq.emplace(dist[nv], nv);
            }
        }
    }

    return dist;
}
