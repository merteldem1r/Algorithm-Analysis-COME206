#ifndef ALGORITHMS_H
#define ALGORITHMS_H

std::vector<int> dfs(const std::vector<std::vector<std::pair<int, int>>> &adj, int start);
std::vector<int> bfs(const std::vector<std::vector<std::pair<int, int>>> &adj, int start);
std::vector<int> dijkstra(const std::vector<std::vector<std::pair<int, int>>> &adj, const int src);

#endif // ALGORITHMS_H