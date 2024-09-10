#include <iostream>
#include <string>
#include <vector>
#include <omp.h>

std::vector<int> naiveStringMatchingParallel(const std::string &text, const std::string &pattern)
{
    std::vector<int> occurrences;
    int n = text.length();
    int m = pattern.length();

    #pragma omp parallel for shared(text, pattern, occurrences)
    for (int i = 0; i <= n - m; ++i)
    {
        bool found = true;
        for (int j = 0; j < m; ++j)
        {
            if (text[i + j] != pattern[j])
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            #pragma omp critical
            occurrences.push_back(i);
        }
    }

    return occurrences;
}

int main()
{
    std::string text = "ababcabcabababd"; // Example text
    std::string pattern = "ababd";        // Pattern to search for

    std::vector<int> result = naiveStringMatchingParallel(text, pattern);

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