#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

int knapsack(int W, const std::vector<int> &weights, const std::vector<int> &values, int n)
{
    // Create a 2D DP array with (n+1) x (W+1) dimensions
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    // Build the DP table
    #pragma omp parallel for collapse(2)
    for (int i = 1; i <= n; ++i)
    {
        for (int w = 1; w <= W; ++w)
        {
            if (weights[i - 1] <= w)
            {
                // Either take the item or leave it
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            }
            else
            {
                // If the item can't be taken, just carry forward the previous value
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W]; // Maximum value that can be achieved
}

int main()
{
    int W = 50;                               // Maximum weight capacity of the knapsack
    std::vector<int> weights = {10, 20, 30};  // Weights of items
    std::vector<int> values = {60, 100, 120}; // Values of items
    int n = weights.size();                   // Number of items

    int maxValue = knapsack(W, weights, values, n);

    std::cout << "Maximum value that can be achieved: " << maxValue << std::endl;

    return 0;
}


// Compile with
//g++ -fopenmp -o knapsack knapsack_parallel.cpp
