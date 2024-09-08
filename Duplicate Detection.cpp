#include <iostream>
#include <vector>
#include <unordered_set>

bool hasDuplicates(const std::vector<int> &nums)
{
    std::unordered_set<int> seen; // To store elements we've seen

    for (int num : nums)
    {
        // Check if the number is already in the set
        if (seen.find(num) != seen.end())
        {
            return true; // Duplicate found
        }
        // Add the number to the set
        seen.insert(num);
    }

    return false; // No duplicates
}

int main()
{
    // Example array (you can use a larger array as needed)
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 5}; // 5 is a duplicate

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
