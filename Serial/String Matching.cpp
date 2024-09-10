#include <iostream>
#include <string>
#include <vector>

// Function to perform naive string matching
std::vector<int> naiveStringMatching(const std::string &text, const std::string &pattern)
{
    std::vector<int> occurrences;
    int n = text.length();
    int m = pattern.length();

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
            occurrences.push_back(i); // Pattern found at index i
        }
    }

    return occurrences;
}

int main()
{
    std::string text = "ababcabcabababd"; // Example text
    std::string pattern = "ababd";        // Pattern to search for

    std::vector<int> result = naiveStringMatching(text, pattern);

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
