#pragma once

#include <iostream>

// Graph (weighted/unweighted) - Adjacency List

class Graph
{
private:
    int size;
    bool isDirected;
    bool isWeighted;
    std::vector<std::vector<std::pair<int, int>>> adj; // {node, distance}

public:
    Graph(int s, bool isD = false, bool isW = false)
    {
        size = s;
        adj.resize(s);
        isWeighted = isW;
        isDirected = isD;
    }

    void addEdge(int u, int v, int w = 1)
    {
        if (u < 0 || u >= size || v < 0 || v >= size)
        {
            throw std::out_of_range("Invalid vertex index");
        }

        if (!isWeighted)
        {
            w = 1;
        }

        adj[u].emplace_back(v, w);

        if (!isDirected)
        {
            adj[v].emplace_back(u, w);
        }
    }

    void print() const
    {
        for (int i = 0; i < size; ++i)
        {
            std::cout << i << ": ";

            for (const auto &[neighbor, weight] : adj[i])
            {
                std::cout << "{" << neighbor << ", " << weight << "} ";
            }

            std::cout << "\n";
        }
    }

    // helpers
    int getSize() const
    {
        return size;
    }

    bool getIsDirected() const
    {
        return isDirected;
    }

    bool getIsWeighted() const
    {
        return isWeighted;
    }

    const std::vector<std::vector<std::pair<int, int>>> &getAdj() const
    {
        return adj;
    }
};