#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <ctime>

bool twoSum(const std::vector<int> &nums, int target, std::pair<int, int> &result)
{
    std::unordered_map<int, int> numMap; // To store number and its index

    for (int i = 0; i < nums.size(); ++i)
    {
        int complement = target - nums[i];

        // Check if complement exists in the map
        if (numMap.find(complement) != numMap.end())
        {
            result = {numMap[complement], i}; // Return the indices of the two numbers
            return true;
        }

        // Store the current number and its index
        numMap[nums[i]] = i;
    }

    return false; // No pair found
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
