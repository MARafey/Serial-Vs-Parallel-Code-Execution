#include <iostream>
#include <vector>
#include <omp.h>

void printFibonacciParallel(int n)
{
    std::vector<int> fib(n);

    if (n >= 1)
        fib[0] = 0; // First Fibonacci number
    if (n >= 2)
        fib[1] = 1; // Second Fibonacci number

    // Parallelize the loop using OpenMP
    #pragma omp parallel for shared(fib)
    for (int i = 2; i < n; ++i)
    {
        fib[i] = fib[i - 1] + fib[i - 2]; // Compute the next Fibonacci number
    }

    std::cout << "Fibonacci Series:\n";
    for (int num : fib)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int n = 25; // Number of Fibonacci numbers to generate
    printFibonacciParallel(n);
    return 0;
}