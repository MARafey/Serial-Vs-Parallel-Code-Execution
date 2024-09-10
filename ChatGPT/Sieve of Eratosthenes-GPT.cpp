#include <iostream>
#include <vector>
#include <omp.h> // Include the OpenMP header

std::vector<int> sieveOfEratosthenes(int n)
{
    std::vector<bool> isPrime(n + 1, true); // Create a boolean array and initialize all entries as true
    std::vector<int> primes;                // Vector to store the prime numbers

    // Edge case: Numbers less than 2 are not prime
    if (n < 2)
        return primes;

    // Mark 0 and 1 as non-prime
    isPrime[0] = isPrime[1] = false;

    // Sequential part: Mark multiples of each number as non-prime
    for (int i = 2; i * i <= n; ++i)
    {
        if (isPrime[i])
        {
            // Parallelize the marking of multiples of i
            #pragma omp parallel for schedule(dynamic)
            for (int j = i * i; j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }

    // Collect all prime numbers
    for (int i = 2; i <= n; ++i)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
        }
    }

    return primes;
}

int main()
{
    int n = 100; // Example upper limit

    std::vector<int> primes = sieveOfEratosthenes(n);

    std::cout << "Prime numbers up to " << n << " are:" << std::endl;
    for (int prime : primes)
    {
        std::cout << prime << " ";
    }
    std::cout << std::endl;

    return 0;
}
