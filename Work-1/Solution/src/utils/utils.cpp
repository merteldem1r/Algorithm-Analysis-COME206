#include <iostream>
#include <random>

void fillSortedNumbers(int arr[], int arrSize)
{
    for (int i = 0; i < arrSize; ++i)
    {
        arr[i] = i + 1;
    }
}

void fillRandomNumbers(int arr[], int arrSize)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < arrSize; ++i)
    {
        arr[i] = dis(gen);
    }
}

void printArr(int arr[], int arrSize)
{
    std::cout << "{ ";
    for (int i = 0; i < arrSize; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "}" << std::endl;
}