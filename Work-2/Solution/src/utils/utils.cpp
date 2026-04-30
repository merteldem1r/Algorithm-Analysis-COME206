#include "utils.h"
#include "Graph.h"
#include "algorithms.h"

#include <random>
#include <set>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <climits>

Graph generateRandomGraph(
    int vertexCount,
    int edgeCount,
    bool isDirected,
    bool isWeighted,
    int minWeight,
    int maxWeight)
{
    // base input checks
    if (vertexCount <= 0)
    {
        throw std::invalid_argument("vertexCount must be positive.");
    }

    if (edgeCount < 0)
    {
        throw std::invalid_argument("edgeCount cannot be negative.");
    }

    if (isWeighted)
    {
        if (minWeight <= 0 || maxWeight <= 0)
        {
            throw std::invalid_argument("Dijkstra requires positive edge weights.");
        }

        if (minWeight > maxWeight)
        {
            throw std::invalid_argument("minWeight cannot be greater than maxWeight.");
        }
    }

    // possible edges case
    int maxPossibleEdges;

    if (isDirected)
    {
        maxPossibleEdges = vertexCount * (vertexCount - 1);
    }
    else
    {
        maxPossibleEdges = vertexCount * (vertexCount - 1) / 2;
    }

    if (edgeCount > maxPossibleEdges)
    {
        throw std::invalid_argument("edgeCount is larger than the maximum possible number of edges.");
    }

    // graph creation
    Graph graph(vertexCount, isDirected, isWeighted);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> vertexDist(0, vertexCount - 1);
    std::uniform_int_distribution<int> weightDist(minWeight, maxWeight);

    std::set<std::pair<int, int>> existingEdges;

    while (static_cast<int>(existingEdges.size()) < edgeCount)
    {
        int u = vertexDist(gen);
        int v = vertexDist(gen);

        // self look avoid
        if (u == v)
        {
            continue;
        }

        std::pair<int, int> edgeKey;
        if (isDirected)
        {
            // in directed graphs, 0 -> 1 and 1 -> 0 different
            edgeKey = {u, v};
        }
        else
        {
            // in undirected graphs, 0 -- 1 and 1 -- 0 same
            edgeKey = {std::min(u, v), std::max(u, v)};
        }

        // skip edge if exists
        if (existingEdges.count(edgeKey) > 0)
        {
            continue;
        }

        existingEdges.insert(edgeKey);

        int weight = 1;

        if (isWeighted)
        {
            weight = weightDist(gen);
        }

        graph.addEdge(u, v, weight);
    }

    return graph;
}

void runBenchmarkAndSaveCSV(const std::string &filename, int repetitions)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Could not open CSV file...");
    }

    file << "algorithm,"
         << "vertex_count,"
         << "edge_count,"
         << "density_type,"
         << "is_directed,"
         << "is_weighted,"
         << "reached_vertices,"
         << "repetitions,"
         << "average_time_microseconds\n";

    // graph sizes
    std::vector<int> vertexCounts = {10, 100, 500, 1000};

    // weighted/unweighted graphs options
    std::vector<bool> weightedOptions = {false, true};

    // undirected/directed graph options
    std::vector<bool> directedOptions = {false, true};

    for (int vertexCount : vertexCounts)
    {
        // Density levels
        // Sparse  : 2 edges per vertex
        // Medium  : 5 edges per vertex
        // Dense   : 10 edges per vertex
        std::vector<std::pair<std::string, int>> densityTests = {
            {"sparse", vertexCount * 2},
            {"medium", vertexCount * 5},
            {"dense", vertexCount * 10}};

        for (bool isDirected : directedOptions)
        {
            int maxPossibleEdges;

            if (isDirected)
            {
                maxPossibleEdges = vertexCount * (vertexCount - 1);
            }
            else
            {
                maxPossibleEdges = vertexCount * (vertexCount - 1) / 2;
            }

            for (bool isWeighted : weightedOptions)
            {
                std::set<int> usedEdgeCounts;

                for (const auto &[densityType, rawEdgeCount] : densityTests)
                {
                    int edgeCount = rawEdgeCount;

                    if (edgeCount > maxPossibleEdges)
                    {
                        edgeCount = maxPossibleEdges;
                    }

                    // Avoid duplicated rows such as 45, 45 for n = 10 undirected graphs
                    if (usedEdgeCounts.count(edgeCount) > 0)
                    {
                        continue;
                    }

                    usedEdgeCounts.insert(edgeCount);

                    Graph graph = generateRandomGraph(
                        vertexCount,
                        edgeCount,
                        isDirected,
                        isWeighted,
                        1,
                        20);

                    int startVertex = 0;

                    // --- BFS benchmark
                    std::vector<int> bfsOrder;

                    auto bfsStart = std::chrono::high_resolution_clock::now();

                    for (int i = 0; i < repetitions; ++i)
                    {
                        bfsOrder = bfs(graph.getAdj(), startVertex);
                    }

                    auto bfsEnd = std::chrono::high_resolution_clock::now();

                    auto bfsTotalTime = std::chrono::duration_cast<std::chrono::microseconds>(
                                            bfsEnd - bfsStart)
                                            .count();

                    double bfsAverageTime = static_cast<double>(bfsTotalTime) / repetitions;

                    file << "BFS,"
                         << vertexCount << ","
                         << edgeCount << ","
                         << densityType << ","
                         << (isDirected ? "true" : "false") << ","
                         << (isWeighted ? "true" : "false") << ","
                         << bfsOrder.size() << ","
                         << repetitions << ","
                         << bfsAverageTime << "\n";

                    // --- DFS benchmark
                    std::vector<int> dfsOrder;

                    auto dfsStart = std::chrono::high_resolution_clock::now();

                    for (int i = 0; i < repetitions; ++i)
                    {
                        dfsOrder = dfs(graph.getAdj(), startVertex);
                    }

                    auto dfsEnd = std::chrono::high_resolution_clock::now();

                    auto dfsTotalTime = std::chrono::duration_cast<std::chrono::microseconds>(
                                            dfsEnd - dfsStart)
                                            .count();

                    double dfsAverageTime = static_cast<double>(dfsTotalTime) / repetitions;

                    file << "DFS,"
                         << vertexCount << ","
                         << edgeCount << ","
                         << densityType << ","
                         << (isDirected ? "true" : "false") << ","
                         << (isWeighted ? "true" : "false") << ","
                         << dfsOrder.size() << ","
                         << repetitions << ","
                         << dfsAverageTime << "\n";

                    // --- Dijkstra benchmark
                    std::vector<int> distances;

                    auto dijkstraStart = std::chrono::high_resolution_clock::now();

                    for (int i = 0; i < repetitions; ++i)
                    {
                        distances = dijkstra(graph.getAdj(), startVertex);
                    }

                    auto dijkstraEnd = std::chrono::high_resolution_clock::now();

                    auto dijkstraTotalTime = std::chrono::duration_cast<std::chrono::microseconds>(
                                                 dijkstraEnd - dijkstraStart)
                                                 .count();

                    double dijkstraAverageTime =
                        static_cast<double>(dijkstraTotalTime) / repetitions;

                    int reachableCount = 0;

                    for (int distance : distances)
                    {
                        if (distance != INT_MAX)
                        {
                            reachableCount++;
                        }
                    }

                    file << "Dijkstra,"
                         << vertexCount << ","
                         << edgeCount << ","
                         << densityType << ","
                         << (isDirected ? "true" : "false") << ","
                         << (isWeighted ? "true" : "false") << ","
                         << reachableCount << ","
                         << repetitions << ","
                         << dijkstraAverageTime << "\n";
                }
            }
        }
    }

    file.close();

    std::cout << "Benchmark results saved to: " << filename << "\n";
}