#include <iostream>
#include <vector>
#include <omp.h>

void printFibonacci(int n)
{
    std::vector<int> fib(n);

    if (n >= 1)
        fib[0] = 0; // First Fibonacci number
    if (n >= 2)
        fib[1] = 1; // Second Fibonacci number

    // Parallel computation of Fibonacci series using OpenMP
    #pragma omp parallel for
    for (int i = 2; i < n; ++i)
    {
        fib[i] = fib[i - 1] + fib[i - 2]; // Compute Fibonacci number
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

    // Set the number of threads to use in parallel
    omp_set_num_threads(4); // You can adjust this based on your hardware

    printFibonacci(n);
    return 0;
}
