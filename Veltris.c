#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 101
#define INF INT_MAX

// Structure to represent a node in the graph
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

// Structure to represent the graph
struct Graph {
    struct Node* head[N];
};

// Function to create a new node
struct Node* createNode(int v, int w) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with 'n' nodes
struct Graph* createGraph(int n) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    for (int i = 0; i <= n; i++) {
        graph->head[i] = NULL;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int u, int v, int w) {
    struct Node* newNode = createNode(v, w);
    newNode->next = graph->head[u];
    graph->head[u] = newNode;
}

// Function to find the minimum distance vertex from the set of vertices
int minDistance(int dist[], int visited[], int n) {
    int min = INF, min_index;
    for (int v = 1; v <= n; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to implement Dijkstra's algorithm
int networkDelayTime(int times[][3], int timesSize, int n, int k) {
    struct Graph* graph = createGraph(n);
   
    // Construct the graph
    for (int i = 0; i < timesSize; i++) {
        addEdge(graph, times[i][0], times[i][1], times[i][2]);
    }

    int dist[N];
    int visited[N] = {0};

    // Initialize distance array
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }

    // Distance of source vertex from itself is always 0
    dist[k] = 0;

    for (int count = 1; count <= n; count++) {
        int u = minDistance(dist, visited, n);
       
        // Mark the picked vertex as visited
        visited[u] = 1;

        // Update distance value of the adjacent vertices of the picked vertex
        struct Node* temp = graph->head[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;
           
            if (visited[v] == 0 && dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
            temp = temp->next;
        }
    }

    int max_time = 0;
   
    // Find the maximum distance
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) {
            return -1;  // If there is a node that cannot be reached
        }
        if (dist[i] > max_time) {
            max_time = dist[i];
        }
    }
   
    return max_time;
}

int main() {
    int timesSize = 3;
    int times[][3] = {{2,1,1}, {2,3,1}, {3,4,1}};
    int n = 4, k = 2;

    int result = networkDelayTime(times, timesSize, n, k);
    printf("Output: %d\n", result);

    return 0;
}
