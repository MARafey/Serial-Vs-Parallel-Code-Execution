#include <iostream>
#include <string>
#include <omp.h> // Include OpenMP header

bool isPalindrome(const std::string &str)
{
    int length = str.length();
    bool is_palindrome = true;

    // Parallelize the loop using OpenMP
    #pragma omp parallel for
    for (int i = 0; i < length / 2; ++i)
    {
        // Use critical section to update shared variable is_palindrome
        if (str[i] != str[length - 1 - i])
        {
            #pragma omp critical
            {
                is_palindrome = false;
            }
        }
    }

    return is_palindrome;
}

int main()
{
    std::string str = "Saippuakivikauppias"; // Example string

    if (isPalindrome(str))
    {
        std::cout << str << " is a palindrome." << std::endl;
    }
    else
    {
        std::cout << str << " is not a palindrome." << std::endl;
    }

    return 0;
}
