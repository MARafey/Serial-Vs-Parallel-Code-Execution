#include <iostream>
#include <vector>

const int SIZE = 25; // Set the graph size to 25

// Function to perform DFS traversal
void DFSUtil(int v, const std::vector<std::vector<int>> &graph, std::vector<bool> &visited)
{
    // Mark the current node as visited and print it
    visited[v] = true;
    std::cout << v << " ";

    // Recur for all the vertices adjacent to this vertex
    for (int i = 0; i < SIZE; ++i)
    {
        if (graph[v][i] && !visited[i])
        {
            DFSUtil(i, graph, visited);
        }
    }
}

// Function to initialize the DFS traversal
void DFS(const std::vector<std::vector<int>> &graph)
{
    std::vector<bool> visited(SIZE, false);

    // Perform DFS for each vertex
    for (int i = 0; i < SIZE; ++i)
    {
        if (!visited[i])
        {
            DFSUtil(i, graph, visited);
        }
    }
}

int main()
{
    // Initialize a graph with SIZE x SIZE adjacency matrix
    std::vector<std::vector<int>> graph(SIZE, std::vector<int>(SIZE, 0));

    // randonmly adding connection
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (rand() % 2)
            {
                graph[i][j] = 1;
                graph[j][i] = 1;
            }
        }
    }

    std::cout << "Depth-First Traversal of the graph:\n";
    DFS(graph);

    return 0;
}