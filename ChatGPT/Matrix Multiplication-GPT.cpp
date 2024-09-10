#include <iostream>
#include <omp.h>

const int SIZE = 30;

void multiplyMatrices(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE])
{
    // Initialize the result matrix to 0
    #pragma omp parallel for collapse(2) // Parallelize initialization
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            result[i][j] = 0;
        }
    }

    // Multiply matrix A and B, store the result in the result matrix
    #pragma omp parallel for collapse(2) // Parallelize matrix multiplication
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
    multiplyMatrices(A, B, result);

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


// Compile with:
//g++ -fopenmp matrix_multiply.cpp -o matrix_multiply