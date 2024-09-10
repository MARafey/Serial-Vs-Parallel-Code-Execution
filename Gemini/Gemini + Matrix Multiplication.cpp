#include <iostream>
#include <vector>
#include <omp.h>

const int SIZE = 30;

void multiplyMatricesParallel(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE])
{
    // Initialize the result matrix to 0
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            result[i][j] = 0;
        }
    }

    // Parallelize the innermost loop
    #pragma omp parallel for shared(A, B, result)
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int k = 0; k < SIZE; ++k)
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    int A[SIZE][SIZE], B[SIZE][SIZE], result[SIZE][SIZE];

    // Initialize matrices A and B with some values
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            A[i][j] = i + j; // Example values, you can use random or specific values
            B[i][j] = i - j;
        }
    }

    // Multiply matrices A and B
    multiplyMatricesParallel(A, B, result);

    // Display the result matrix
    std::cout << "Resultant Matrix:" << std::endl;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}