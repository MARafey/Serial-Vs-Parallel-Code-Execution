#include <iostream>
#include <vector>
#include <omp.h> // Include OpenMP header

// Function to perform parallel linear search
int parallelLinearSearch(const std::vector<int> &arr, int target)
{
    int index = -1;
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < arr.size(); ++i)
        {
            if (arr[i] == target)
            {
                #pragma omp critical
                {
                    if (index == -1) // Ensure that only the first found index is recorded
                    {
                        index = i;
                    }
                }
            }
        }
    }
    return index;
}

int main()
{
    std::vector<int> arr = {10, 23, 4, 7, 35, 50, 2}; // Example array
    int target = 35;                                  // Target value to search for

    int index = parallelLinearSearch(arr, target);

    if (index != -1)
    {
        std::cout << "Element " << target << " found at index " << index << "." << std::endl;
    }
    else
    {
        std::cout << "Element " << target << " not found in the array." << std::endl;
    }

    return 0;
}
