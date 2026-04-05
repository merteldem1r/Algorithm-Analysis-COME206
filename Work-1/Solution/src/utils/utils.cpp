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
    std::uniform_int_distribution<> dis(1, arrSize);

    for (int i = 0; i < arrSize; ++i)
    {
        arr[i] = dis(gen);
    }
}

void printArr(int arr[], int arrSize)
{
    std::cout << "{";

    if (arrSize <= 10)
    {
        for (int i = 0; i < arrSize; ++i)
        {
            if (i > 0)
            {
                std::cout << ", ";
            }
            std::cout << arr[i];
        }
    }
    else
    {
        for (int i = 0; i < 5; ++i)
        {
            if (i > 0)
            {
                std::cout << ", ";
            }
            std::cout << arr[i];
        }

        std::cout << ", ... , ";

        for (int i = arrSize - 5; i < arrSize; ++i)
        {
            if (i > arrSize - 5)
            {
                std::cout << ", ";
            }
            std::cout << arr[i];
        }
    }

    std::cout << "}" << std::endl;
}