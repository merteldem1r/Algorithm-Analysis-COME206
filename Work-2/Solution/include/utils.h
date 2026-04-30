#ifndef UTILS_H
#define UTILS_H

#include "Graph.h"

Graph generateRandomGraph(int vertexCount, int edgeCount, bool isDirected, bool isWeighted, int minWeight = 1, int maxWeight = 10);
void runBenchmarkAndSaveCSV(const std::string &filename, int repetitions = 1000);

#endif // UTILS_H