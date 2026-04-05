#include <iostream>

// QUICK SORT (Not Adaptive & Not Stable)
// Time Average & Best: O(n logn) Time Worst: O(n^2) || Space: O(n logn)

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low;

    for (int j = low; j <= high - 1; ++j)
    {
        if (arr[j] < pivot)
        {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }

    std::swap(arr[i], arr[high]);
    return i;
}

void quickSort(int A[], int low, int high)
{
    if (low >= high)
        return;

    int pi = partition(A, low, high);
    quickSort(A, low, pi - 1);
    quickSort(A, pi + 1, high);
}
