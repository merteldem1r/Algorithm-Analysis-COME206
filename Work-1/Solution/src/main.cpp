#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include "utils.h"
#include "algorithms.h"

// Test array sizes as per directive
const int SIZES[] = {100, 1000, 5000, 10000, 20000};
const int NUM_SIZES = 5;
const int NUM_RUNS = 5; // Multiple runs to average results

// Timing helper function
long long timeAlgorithmInMicroseconds(int algorithm, int arr[], int size)
{
    // Create copies for each algorithm
    int *arrCopy = new int[size];
    std::memcpy(arrCopy, arr, size * sizeof(int));

    auto start = std::chrono::high_resolution_clock::now();

    if (algorithm == 0) // Binary Search
    {
        // For binary search, we need sorted array
        int *sortedArr = new int[size];
        std::memcpy(sortedArr, arr, size * sizeof(int));
        mergeSort(sortedArr, size, 0, size - 1);
        binarySearch(sortedArr, size, sortedArr[size / 2]);
        delete[] sortedArr;
    }
    else if (algorithm == 1) // Merge Sort
    {
        mergeSort(arrCopy, size, 0, size - 1);
    }
    else if (algorithm == 2) // Quick Sort
    {
        quickSort(arrCopy, 0, size - 1);
    }

    auto end = std::chrono::high_resolution_clock::now();
    long long duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    delete[] arrCopy;
    return duration;
}

int main()
{
    std::cout << "========================================" << std::endl;
    std::cout << "Algorithm Performance Analysis" << std::endl;
    std::cout << "Testing: Binary Search, Merge Sort, Quick Sort" << std::endl;
    std::cout << "========================================" << std::endl
              << std::endl;

    // Create time_results directory if needed
    system("mkdir -p analysis/time_results");

    // Open CSV file for results
    std::ofstream csvFile("analysis/time_results/results.csv");
    csvFile << "Size,BinarySearch,MergeSort,QuickSort\n";

    // For each array size
    for (int s = 0; s < NUM_SIZES; ++s)
    {
        int size = SIZES[s];
        std::cout << "Testing with array size: " << size << std::endl;

        // Generate base random array
        int *baseArr = new int[size];
        fillRandomNumbers(baseArr, size);

        // Run each algorithm multiple times and compute average
        long long bsTime = 0, msTime = 0, qsTime = 0;

        for (int run = 0; run < NUM_RUNS; ++run)
        {
            bsTime += timeAlgorithmInMicroseconds(0, baseArr, size);
            msTime += timeAlgorithmInMicroseconds(1, baseArr, size);
            qsTime += timeAlgorithmInMicroseconds(2, baseArr, size);
        }

        // Compute averages
        long long bsAvg = bsTime / NUM_RUNS;
        long long msAvg = msTime / NUM_RUNS;
        long long qsAvg = qsTime / NUM_RUNS;

        // Print to console
        std::cout << "  Binary Search: " << bsAvg << " µs" << std::endl;
        std::cout << "  Merge Sort:    " << msAvg << " µs" << std::endl;
        std::cout << "  Quick Sort:    " << qsAvg << " µs" << std::endl
                  << std::endl;

        // Write to CSV
        csvFile << size << "," << bsAvg << "," << msAvg << "," << qsAvg << "\n";

        delete[] baseArr;
    }

    csvFile.close();
    std::cout << "========================================" << std::endl;
    std::cout << "Results saved to: analysis/time_results/results.csv" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}