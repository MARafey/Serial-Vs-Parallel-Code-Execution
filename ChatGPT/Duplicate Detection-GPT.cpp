#include <iostream>
#include <vector>
#include <unordered_set>
#include <omp.h>

bool hasDuplicates(const std::vector<int> &nums)
{
    // To track if any thread found a duplicate
    bool foundDuplicate = false;

    // Thread-local storage for each thread's set of seen numbers
    std::unordered_set<int> globalSeen;

    #pragma omp parallel
    {
        // Each thread has its own unordered set to avoid race conditions
        std::unordered_set<int> localSeen;

        // Parallel for loop
        #pragma omp for
        for (size_t i = 0; i < nums.size(); ++i)
        {
            // If a duplicate is found, set foundDuplicate to true and exit
            if (localSeen.find(nums[i]) != localSeen.end())
            {
                foundDuplicate = true;
                #pragma omp cancel for
            }

            localSeen.insert(nums[i]);
        }

        // Critical section to combine thread-local seen sets into the global seen set
        #pragma omp critical
        {
            for (const int &num : localSeen)
            {
                if (globalSeen.find(num) != globalSeen.end())
                {
                    foundDuplicate = true;
                    break;
                }
                globalSeen.insert(num);
            }
        }
    }

    return foundDuplicate;
}

int main()
{
    // Example array with a duplicate
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 5};

    if (hasDuplicates(nums))
    {
        std::cout << "The array contains duplicates." << std::endl;
    }
    else
    {
        std::cout << "The array does not contain duplicates." << std::endl;
    }

    return 0;
}
