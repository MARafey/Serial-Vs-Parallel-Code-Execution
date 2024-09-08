#include <iostream>
#include <vector>

// Function to compute the sum and average of an array
void sumAndAverage(const std::vector<int> &arr, int &sum, double &average)
{
    sum = 0;
    int n = arr.size();

    if (n == 0)
    {
        average = 0.0; // To handle the case of an empty array
        return;
    }

    for (int value : arr)
    {
        sum += value;
    }

    average = static_cast<double>(sum) / n;
}

int main()
{
    std::vector<int> arr; // Example array
    int size = 100;
    for (int i = 0; i < size; ++i)
    {
        arr.push_back(i);
    }
    int sum;
    double average;

    sumAndAverage(arr, sum, average);

    std::cout << "Sum of array elements: " << sum << std::endl;
    std::cout << "Average of array elements: " << average << std::endl;

    return 0;
}
