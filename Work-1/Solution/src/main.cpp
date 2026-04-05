#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <random>
#include "utils.h"
#include "algorithms.h"

const int SIZES[] = {100, 1000, 5000, 10000, 20000};
const int NUM_SIZES = 5;
const int NUM_RUNS = 5; // Multiple runs to average results

// Timing helper function
long long timeAlgorithmInMicroseconds(int algorithm, int arr[], int size, int *sortedArr = nullptr, int target = -1)
{
    // Create copies for each algorithm
    int *arrCopy = new int[size];
    std::memcpy(arrCopy, arr, size * sizeof(int));

    auto start = std::chrono::high_resolution_clock::now();

    if (algorithm == 0) // Binary Search (on pre-sorted array)
    {
        // Timer only measures the search with random target
        binarySearch(sortedArr, size, target);
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

    // Random number generator for target values
    std::random_device rd;
    std::mt19937 gen(rd());

    // For each array size
    for (int s = 0; s < NUM_SIZES; ++s)
    {
        int size = SIZES[s];
        std::cout << "Testing with array size: " << size << std::endl;

        // Generate base random array
        int *baseArr = new int[size];
        fillRandomNumbers(baseArr, size);

        // Create pre-sorted array for binary search (outside timing)
        int *sortedArr = new int[size];
        fillSortedNumbers(sortedArr, size);

        // Run each algorithm multiple times and compute average
        long long bsTime = 0, msTime = 0, qsTime = 0;
        std::uniform_int_distribution<> dis(1, size);

        for (int run = 0; run < NUM_RUNS; ++run)
        {
            int randomTarget = dis(gen); // Generate random target for binary search
            std::cout << "  Run " << run + 1 << "/" << NUM_RUNS << " with target: " << randomTarget << std::endl;
            bsTime += timeAlgorithmInMicroseconds(0, baseArr, size, sortedArr, randomTarget);
            msTime += timeAlgorithmInMicroseconds(1, baseArr, size, sortedArr);
            qsTime += timeAlgorithmInMicroseconds(2, baseArr, size, sortedArr);
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

        delete[] sortedArr;
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