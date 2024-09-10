 #include <iostream>
#include <string>
#include <omp.h>

bool isPalindromeParallel(const std::string &str)
{
    int length = str.length();

    #pragma omp parallel for shared(str) reduction(|| : result)
    for (int i = 0; i < length / 2; ++i)
    {
        if (str[i] != str[length - 1 - i])
        {
            result = true; // Found a mismatch
            break;
        }
    }

    return !result;
}

int main()
{
    std::string str = "Saippuakivikauppias"; // Example string

    if (isPalindromeParallel(str))
    {
        std::cout << str << " is a palindrome." << std::endl;
    }
    else
    {
        std::cout << str << " is not a palindrome." << std::endl;
    }

    return 0;
}