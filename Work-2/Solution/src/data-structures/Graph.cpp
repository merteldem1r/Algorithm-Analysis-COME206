#include <iostream>

// Graph - Adjacency List

class Graph
{
private:
    int size = 0;
    bool isWeighted = false;
    std::vector<std::vector<std::pair<int, int>>> adj; // {node, distance}

public:
    Graph(int s, bool isW)
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

    // helpers
    int getSize()
    {
        return size;
    }

    std::vector<std::vector<std::pair<int, int>>> &getAdj()
    {
        return adj;
    }
};