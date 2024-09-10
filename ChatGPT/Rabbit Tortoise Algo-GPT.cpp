#include <iostream>
#include <vector>
#include <unordered_set>
#include <omp.h>

bool hasCycle(const std::vector<int> &arr)
{
    if (arr.empty())
        return false;

    // Number of threads to use
    const int num_threads = 4;
    bool cycle_detected = false;

    #pragma omp parallel num_threads(num_threads) shared(cycle_detected)
    {
        std::unordered_set<int> visited;
        #pragma omp for
        for (int start_index = 0; start_index < arr.size(); ++start_index)
        {
            if (cycle_detected) continue;

            int current = start_index;
            visited.clear();
            
            while (current >= 0 && current < arr.size())
            {
                if (visited.find(current) != visited.end())
                {
                    #pragma omp critical
                    {
                        cycle_detected = true;
                    }
                    break;
                }

                visited.insert(current);
                current = arr[current];
            }
        }
    }

    return cycle_detected;
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

    if (hasCycle(arr))
    {
        std::cout << "The array contains a cycle." << std::endl;
    }
    else
    {
        std::cout << "The array does not contain a cycle." << std::endl;
    }

    return 0;
}
