#include <iostream>

// Graph (weighted/unweighted) - Adjacency List

class Graph
{
private:
    int size = 0;
    bool isWeighted = false;
    std::vector<std::vector<std::pair<int, int>>> adj; // {node, distance}

public:
    Graph(int s, bool isW = false)
    {
        size = s;
        adj.reserve(s);
        isWeighted = isW;
    }

    int addEdge(int i, int j, int w = INT_MAX)
    {
        adj[i].emplace_back(j, w);
        adj[j].emplace_back(i, w);
    }

    void print()
    {
        for (int i = 0; i < adj.size(); ++i)
        {
            std::cout << i << ": ";
            for (auto &[n, w] : adj[i])
            {
                std::cout << "{" << n << ", " << w << "} ";
            }
            std::cout << std::endl;
        }
    }

    // helpers
    std::vector<std::vector<std::pair<int, int>>> &getAdj()
    {
        return adj;
    }
};