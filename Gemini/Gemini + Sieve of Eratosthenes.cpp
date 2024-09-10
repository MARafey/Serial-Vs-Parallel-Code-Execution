#include <iostream>
#include <vector>
#include <omp.h>

std::vector<int> sieveOfEratosthenesParallel(int n)
{
    std::vector<bool> isPrime(n + 1, true);
    std::vector<int> primes;

    // ... (same as in your original code)

    #pragma omp parallel for shared(isPrime)
    for (int i = 2; i * i <= n; ++i)
    {
        if (isPrime[i])
        {
            // Mark multiples of i as non-prime
            #pragma omp for schedule(static, 100)
            for (int j = i * i; j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }

     for (int i = 2; i <= n; ++i)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
        }
    }

    return primes;
}
}

int main()
{
    int n = 100; // Example upper limit

    std::vector<int> primes = sieveOfEratosthenesParallel(n);

    std::cout << "Prime numbers up to " << n << " are:" << std::endl;
    for (int prime : primes)
    {
        std::cout << prime << " ";
    }
    std::cout << std::endl;

    return 0;
}