#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <ctime>
#include <omp.h>

bool twoSum(const std::vector<int> &nums, int target, std::pair<int, int> &result)
{
    std::unordered_map<int, int> numMap; // To store number and its index
    bool found = false;

    // Use OpenMP to parallelize the loop
    #pragma omp parallel for shared(numMap, found)
    for (int i = 0; i < nums.size(); ++i)
    {
        if (found) continue;  // Skip further iterations if the pair is found

        int complement = target - nums[i];

        // Use a critical section to protect shared access to the map
        #pragma omp critical
        {
            // Check if complement exists in the map
            if (numMap.find(complement) != numMap.end() && !found)
            {
                result = {numMap[complement], i}; // Return the indices of the two numbers
                found = true;
            }
            // Store the current number and its index
            numMap[nums[i]] = i;
        }
    }

    return found; // Return whether the pair was found
}

int main()
{
    // Large array (example)
    std::vector<int> nums; // You can expand this with larger data
    int count = 50;
    srand(time(0));
    for (int i = 0; i < count; i++)
    {
        nums.push_back(rand() % 100);
    }

    int target = 17;
    std::pair<int, int> result;

    if (twoSum(nums, target, result))
    {
        std::cout << "Pair found at indices: " << result.first << " and " << result.second << std::endl;
        std::cout << "Numbers are: " << nums[result.first] << " and " << nums[result.second] << std::endl;
    }
    else
    {
        std::cout << "No pair found that adds up to " << target << std::endl;
    }

    return 0;
}
