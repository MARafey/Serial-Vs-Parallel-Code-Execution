#include <iostream>
#include <vector>
#include <omp.h>

// Function to merge two halves of the array
void merge(std::vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1);
    std::vector<int> R(n2);

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; ++i)
    {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j)
    {
        R[j] = arr[mid + 1 + j];
    }

    // Merge the temporary arrays back into arr[left..right]
    int i = 0;    // Initial index of the first subarray
    int j = 0;    // Initial index of the second subarray
    int k = left; // Initial index of the merged subarray

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            ++i;
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// Function to perform parallel merge sort
void parallelMergeSort(std::vector<int> &arr, int left, int right, int threads)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // If more than one thread is available, split into two parallel sections
        if (threads > 1)
        {
            #pragma omp parallel sections
            {
                #pragma omp section
                {
                    parallelMergeSort(arr, left, mid, threads / 2);
                }
                #pragma omp section
                {
                    parallelMergeSort(arr, mid + 1, right, threads / 2);
                }
            }
        }
        else // Perform sequential merge sort if only one thread is available
        {
            parallelMergeSort(arr, left, mid, 1);
            parallelMergeSort(arr, mid + 1, right, 1);
        }

        // Merge the sorted halves
        merge(arr, left, mid, right);
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

    int maxThreads = omp_get_max_threads(); // Get the maximum number of threads available

    // Perform parallel merge sort
    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelMergeSort(arr, 0, arr.size() - 1, maxThreads);
        }
    }

    std::cout << "Sorted array:\n";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
