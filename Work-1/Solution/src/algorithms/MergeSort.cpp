#include <iostream>

// MERGE SORT (Not Adaptive & Stable)
// Time Worst & Best & Average: O(n logn) || Space: O(n)

/*
    Example merge() functions letters:

        l        m              h
       [1, 3, 5, 7, 12, 15, 20, 21]
        i           j

*/

void merge(int A[], int l, int mid, int h)
{
    int i = l;
    int j = mid + 1;

    int *tempArr = new int[h + 1];
    int k = l;

    while (i <= mid && j <= h)
    {
        if (A[i] < A[j])
            tempArr[k++] = A[i++];
        else
            tempArr[k++] = A[j++];
    }

    for (; i <= mid; ++i)
        tempArr[k++] = A[i];

    for (; j <= h; ++j)
        tempArr[k++] = A[j];

    for (i = l; i <= h; ++i)
    {
        A[i] = tempArr[i];
    }

    delete[] tempArr;
}

void mergeSort(int A[], int arrSize, int l, int h)
{
    if (l >= h)
        return;

    int mid = l + (h - l) / 2;

    mergeSort(A, arrSize, l, mid);
    mergeSort(A, arrSize, mid + 1, h);
    merge(A, l, mid, h);
}
