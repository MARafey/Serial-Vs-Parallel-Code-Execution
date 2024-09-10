#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <ctime>
#include <omp.h>

bool twoSumParallel(const std::vector<int>& nums, int target, std::pair<int, int>& result) {
    std::unordered_map<int, int> numMap;

    #pragma omp parallel for shared(nums, target, numMap, result)
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];

        // Use a critical section to protect the hash map and result update
        #pragma omp critical
        {
            if (numMap.find(complement) != numMap.end()) {
                result = {numMap[complement], i};
                return true;
            }

            numMap[nums[i]] = i;
        }
    }

    return false;
}

int main() {
    // Large array (example)
    std::vector<int> nums; // You can expand this with larger data
    int count = 50;
    srand(time(0));
    for (int i = 0; i < count; i++) {
        nums.push_back(rand() % 100);
    }

    int target = 17;
    std::pair<int, int> result;

    if (twoSumParallel(nums, target, result)) {
        std::cout << "Pair found at indices: " << result.first << " and " << result.second << std::endl;
        std::cout << "Numbers are: " << nums[result.first] << " and " << nums[result.second] << std::endl;
    } else {
        std::cout << "No pair found that adds up to " << target << std::endl;
    }

    return 0;
}