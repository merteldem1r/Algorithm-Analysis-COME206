#include <iostream>

// Time Complexity: O(log n) | Space Complexity: O(1)
int binarySearch(int arr[], int arrSize, int target)
{
    int left = 0;
    int right = arrSize - 1;

    while (left <= right)
    {
        const int mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}