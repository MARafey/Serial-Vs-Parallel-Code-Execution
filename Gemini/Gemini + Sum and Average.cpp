#include <iostream>
#include <vector>
#include <omp.h>

void sumAndAverageParallel(const std::vector<int> &arr, int &sum, double &average)
{
    sum = 0;
    int n = arr.size();

    if (n == 0)
    {
        average = 0.0;
        return;
    }

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; ++i)
    {
        sum += arr[i];
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

    sumAndAverageParallel(arr, sum, average);

    std::cout << "Sum of array elements: " << sum << std::endl;
    std::cout << "Average of array elements: " << average << std::endl;

    return 0;
}