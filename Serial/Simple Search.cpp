#include <iostream>
#include <vector>

// Function to perform linear search
int linearSearch(const std::vector<int> &arr, int target)
{
    for (int i = 0; i < arr.size(); ++i)
    {
        if (arr[i] == target)
        {
            return i; // Return the index if the target is found
        }
    }
    return -1; // Return -1 if the target is not found
}

int main()
{
    std::vector<int> arr = {10, 23, 4, 7, 35, 50, 2}; // Example array
    int target = 35;                                  // Target value to search for

    int index = linearSearch(arr, target);

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
