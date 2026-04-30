#include <iostream>
#include "algorithms.h"

std::vector<int> bfs(const std::vector<std::vector<std::pair<int, int>>> &adj, int start) // Time: O(V + E) | Space: O(V)
{
    std::vector<bool> visited(adj.size(), false);
    std::queue<int> q;
    std::vector<int> visitOrder;

    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int vertex = q.front();
        q.pop();

        visitOrder.push_back(vertex);

        for (const auto &[neighbor, weight] : adj[vertex])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return visitOrder;
}
