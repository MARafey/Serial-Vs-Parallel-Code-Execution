#include <iostream>
#include <string>
#include <omp.h>

void reverseString(std::string &str)
{
    int n = str.length();
    
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < n / 2; ++i)
        {
            // Swap characters at indices i and n - i - 1
            char temp = str[i];
            str[i] = str[n - i - 1];
            str[n - i - 1] = temp;
        }
    }
}

int main()
{
    std::string str = "hello world my naem is rafey i like to talk and smoke weed but weed is not always food for me so that makes me sadd you what sadd is right ik right its depressing"; // Example string

    reverseString(str);

    std::cout << "Reversed string: " << str << std::endl;

    return 0;
}
