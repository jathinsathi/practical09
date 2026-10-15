#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure to represent an edge (destination vertex, weight)
struct Edge {
    int dest;
    int weight;
};

// Function to find and print the Minimum Spanning Tree using Prim's Algorithm
void primMST(const vector<vector<Edge>>& graph, int V) {
    // Priority queue to store pairs of (weight, vertex)
    // std::greater ensures the smallest weight is always at the top (Min-Heap)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int src = 0; // Choose 0 as the starting vertex

    // Vectors to store minimum weights, parents, and tracking sets
    vector<int> key(V, INT_MAX);    // Tracks the minimum edge weight to connect each vertex to MST
    vector<int> parent(V, -1);      // Tracks the parent node to reconstruct the MST
    vector<bool> inMST(V, false);   // Tracks if a vertex is already included in the MST

    // Initialize the source vertex
    pq.push({0, src});
    key[src] = 0;

    int totalWeight = 0;

    cout << "Edges in the Minimum Spanning Tree:\n";

    while (!pq.empty()) {
        // Extract the vertex with the minimum edge weight connecting it to the MST
        int u = pq.top().second;
        pq.pop();

        // If the vertex is already in the MST, skip it
        if (inMST[u]) continue;

        // Include the vertex in the MST
        inMST[u] = true;
        totalWeight += key[u];

        // Print the edge (skip the root node since it has no parent)
        if (parent[u] != -1) {
            cout << parent[u] << " - " << u << " \tWeight: " << key[u] << "\n";
        }

        // Traverse all adjacent vertices of u
        for (const auto& edge : graph[u]) {
            int v = edge.dest;
            int weight = edge.weight;

            // If v is not yet in the MST and the edge weight u-v is smaller than its current key
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    cout << "\nTotal Weight of Minimum Spanning Tree: " << totalWeight << "\n";
}

int main() {
    int V = 5; // Number of vertices
    vector<vector<Edge>> graph(V);

    // Graph Construction (Undirected Graph)
    // addEdge(u, v, weight) means pushing to both u and v lists
    
    // Edges from node 0
    graph[0].push_back({1, 2});
    graph[0].push_back({3, 6});

    // Edges from node 1
    graph[1].push_back({0, 2});
    graph[1].push_back({2, 3});
    graph[1].push_back({3, 8});
    graph[1].push_back({4, 5});

    // Edges from node 2
    graph[2].push_back({1, 3});
    graph[2].push_back({4, 7});

    // Edges from node 3
    graph[3].push_back({0, 6});
    graph[3].push_back({1, 8});

    // Edges from node 4
    graph[4].push_back({1, 5});
    graph[4].push_back({2, 7});

    // Run the algorithm
    primMST(graph, V);

    return 0;
}
