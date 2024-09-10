#include <iostream>
#include <vector>
#include <omp.h>

void merge(std::vector<int> &arr, int left, int mid, int right)
{
    // ... (same as in your original code)
}

void mergeSortParallel(std::vector<int> &arr, int left, int right)
{
    if (right - left > 100) // Adjust the threshold as needed
    {
        int mid = left + (right - left) / 2;

        #pragma omp task firstprivate(arr, left, mid)
        mergeSortParallel(arr, left, mid);

        #pragma omp task firstprivate(arr, mid + 1, right)
        mergeSortParallel(arr, mid + 1, right);

        #pragma omp taskwait
        merge(arr, left, mid, right);
    }
    else
    {
        // Use the sequential merge sort for smaller subarrays
        mergeSort(arr, left, right);
    }
}

int main()
{
    std::vector<int> arr;
    int size = 1000;
    for (int i = 0; i < size; ++i)
    {
        arr.push_back(rand() % 1000);
    }

    std::cout << "Original array:\n";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    mergeSortParallel(arr, 0, arr.size() - 1);

    std::cout << "Sorted array:\n";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}