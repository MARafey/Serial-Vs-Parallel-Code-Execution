#include <iostream>
#include <vector>
#include <omp.h>

int linearSearchParallel(const std::vector<int> &arr, int target)
{
    int result = -1;

    #pragma omp parallel for shared(arr, target) reduction(max:result)
    for (int i = 0; i < arr.size(); ++i)
    {
        if (arr[i] == target)
        {
            result = i;
            break;
        }
    }

    return result;
}

int main()
{
    std::vector<int> arr = {10, 23, 4, 7, 35, 50, 2}; // Example array
    int target = 35;                                  // Target value to search for

    int index = linearSearchParallel(arr, target);

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