#include <iostream>
#include <string>

bool isPalindrome(const std::string &str)
{
    int length = str.length();

    for (int i = 0; i < length / 2; ++i)
    {
        if (str[i] != str[length - 1 - i])
        {
            return false;
        }
    }

    return true;
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
