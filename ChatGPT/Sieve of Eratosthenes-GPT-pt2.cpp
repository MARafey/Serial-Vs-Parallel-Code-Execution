//-----------------------------------------------------------------
//SOLUTION 2
//-----------------------------------------------------------------
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

void markNonPrimes(std::vector<bool>& isPrime, int start, int end, int prime) {
    for (int j = start; j <= end; j += prime) {
        isPrime[j] = false;
    }
}

std::vector<int> sieveOfEratosthenes(int n) {
    std::vector<bool> isPrime(n + 1, true); // Create a boolean array and initialize all entries as true
    std::vector<int> primes;                // Vector to store the prime numbers

    // Edge case: Numbers less than 2 are not prime
    if (n < 2)
        return primes;

    // Mark 0 and 1 as non-prime
    isPrime[0] = isPrime[1] = false;

    int numThreads = std::thread::hardware_concurrency(); // Number of threads to use
    std::vector<std::thread> threads(numThreads);

    for (int i = 2; i * i <= n; ++i) {
        if (isPrime[i]) {
            int start = i * i;
            int step = i;
            
            // Parallelize marking of multiples of i
            for (int t = 0; t < numThreads; ++t) {
                int segment_start = start + t * (n - start + 1) / numThreads;
                int segment_end = start + (t + 1) * (n - start + 1) / numThreads - 1;

                if (segment_start <= n) {
                    if (segment_end > n) {
                        segment_end = n;
                    }
                    threads[t] = std::thread(markNonPrimes, std::ref(isPrime), segment_start, segment_end, step);
                }
            }
            // Join all threads
            for (auto& th : threads) {
                if (th.joinable()) {
                    th.join();
                }
            }
        }
    }

    // Collect all prime numbers
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

int main() {
    int n = 100; // Example upper limit

    std::vector<int> primes = sieveOfEratosthenes(n);

    std::cout << "Prime numbers up to " << n << " are:" << std::endl;
    for (int prime : primes) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;

    return 0;
}
