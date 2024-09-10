#include <iostream>
#include <string>
#include <vector>
#include <omp.h>

// Function to perform parallel naive string matching
std::vector<int> parallelNaiveStringMatching(const std::string &text, const std::string &pattern)
{
    std::vector<int> occurrences;
    int n = text.length();
    int m = pattern.length();

    // Adjust chunk size to balance load among threads
    int chunkSize = 10;

    #pragma omp parallel
    {
        std::vector<int> localOccurrences;
        
        #pragma omp for schedule(dynamic, chunkSize)
        for (int i = 0; i <= n - m; ++i)
        {
            int j;
            for (j = 0; j < m; ++j)
            {
                if (text[i + j] != pattern[j])
                {
                    break;
                }
            }
            if (j == m)
            {
                localOccurrences.push_back(i); // Pattern found at index i
            }
        }

        // Critical section to avoid race condition when adding to occurrences
        #pragma omp critical
        {
            occurrences.insert(occurrences.end(), localOccurrences.begin(), localOccurrences.end());
        }
    }

    return occurrences;
}

int main()
{
    std::string text = "ababcabcabababd"; // Example text
    std::string pattern = "ababd";        // Pattern to search for

    // Set the number of threads (optional)
    omp_set_num_threads(4); // Adjust as needed

    std::vector<int> result = parallelNaiveStringMatching(text, pattern);

    if (!result.empty())
    {
        std::cout << "Pattern found at indices: ";
        for (int index : result)
        {
            std::cout << index << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Pattern not found in the text." << std::endl;
    }

    return 0;
}
