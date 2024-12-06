#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp
{
    std::vector<std::vector<int>> graph;             // Adjacency list for the bipartite graph
    std::vector<int> matchLeft, matchRight, visited; // Matching arrays and visited timestamp array
    int leftSize, rightSize, timestamp, matchCount;  // Sizes of left and right sets, current timestamp, and match count

    // Constructor to initialize the bipartite graph with given sizes
    HopcroftKarp(int leftNodes, int rightNodes) : leftSize(leftNodes + 1), rightSize(rightNodes + 1)
    {
        assert(0 <= leftSize && 0 <= rightSize); // Ensure valid sizes
        matchLeft.assign(leftSize, -1);          // Initialize match arrays with -1 (no match)
        matchRight.assign(rightSize, -1);
        visited.resize(leftSize); // Initialize visited array
        graph.resize(leftSize);   // Initialize adjacency list
        matchCount = 0;           // Initialize match count
        timestamp = 0;            // Initialize timestamp
    }

    // Function to add an edge between a left node and a right node
    void addEdge(int leftNode, int rightNode)
    {
        assert(0 <= leftNode && leftNode < leftSize && 0 <= rightNode && rightNode < rightSize); // Ensure valid nodes
        graph[leftNode].push_back(rightNode);                                                    // Add edge to the adjacency list
    }

    // Depth First Search to find augmenting paths
    bool depthFirstSearch(int leftNode)
    {
        visited[leftNode] = timestamp;        // Mark the node as visited with the current timestamp
        for (int rightNode : graph[leftNode]) // Iterate over all adjacent right nodes
        {
            if (matchRight[rightNode] == -1) // If the right node is not matched
            {
                matchRight[rightNode] = leftNode; // Match the nodes
                matchLeft[leftNode] = rightNode;
                return true; // Augmenting path found
            }
        }
        for (int rightNode : graph[leftNode]) // Iterate again to find alternate paths
        {
            if (visited[matchRight[rightNode]] != timestamp && depthFirstSearch(matchRight[rightNode])) // Recursive DFS
            {
                matchLeft[leftNode] = rightNode; // Match the nodes
                matchRight[rightNode] = leftNode;
                return true; // Augmenting path found
            }
        }
        return false; // No augmenting path found
    }

    // Function to find the maximum matching in the bipartite graph
    int findMaximumMatching()
    {
        while (true)
        {
            timestamp++;        // Increment timestamp for a new round of DFS
            int newMatches = 0; // Count of new matches in this round
            for (int i = 0; i < leftSize; i++)
            {
                if (matchLeft[i] == -1 && depthFirstSearch(i)) // If the left node is not matched, perform DFS
                {
                    newMatches++; // Increment new matches count
                }
            }
            if (newMatches == 0) // If no new matches found, break the loop
                break;
            matchCount += newMatches; // Add new matches to the total match count
        }
        return matchCount; // Return the total number of matches
    }
};
