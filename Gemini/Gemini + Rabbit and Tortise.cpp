#include <iostream>
#include <vector>
#include <unordered_set>
#include <omp.h>

bool hasCycleParallel(const std::vector<int> &arr)
{
    if (arr.empty())
        return false;

    std::unordered_set<int> visited;

    #pragma omp parallel shared(arr, visited)
    {
        int current = omp_get_thread_num(); // Start at the thread's index

        while (current >= 0 && current < arr.size())
        {
            #pragma omp critical
            {
                if (visited.find(current) != visited.end())
                {
                    return true; // Cycle detected
                }

                visited.insert(current);
            }

            current = arr[current];
        }
    }

    return false;
}

int main()
{
    // Define a large array with a cycle
    int size = 1000; // Size of the array
    std::vector<int> arr(size, -1);

    // Initialize array values to form a cycle
    for (int i = 0; i < size - 1; ++i)
    {
        arr[i] = i + 1;
    }
    arr[size - 1] = 500; // Creating a cycle by pointing back to index 500

    if (hasCycleParallel(arr))
    {
        std::cout << "The array contains a cycle." << std::endl;
    }
    else
    {
        std::cout << "The array does not contain a cycle." << std::endl;
    }

    return 0;
}