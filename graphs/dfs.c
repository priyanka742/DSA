#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Node* adjacencyList[], int src, int dest) {
    // Add an edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = adjacencyList[src];
    adjacencyList[src] = newNode;
}

void dfsUtil(int vertex, Node* adjacencyList[], bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);

    Node* current = adjacencyList[vertex];
    while (current != NULL) {
        int neighbor = current->vertex;
        if (!visited[neighbor]) {
            dfsUtil(neighbor, adjacencyList, visited);
        }
        current = current->next;
    }
}

void dfs(Node* adjacencyList[], int numVertices, int startVertex) {
    bool visited[MAX_VERTICES] = {false};

    printf("DFS Traversal: ");
    dfsUtil(startVertex, adjacencyList, visited);
    printf("\n");
}

int main() {
    FILE* file;
    char filename[100];
    int numVertices, vertex1, vertex2;

    // Open the file
    printf("Enter the filename: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Read the number of vertices from the file
    fscanf(file, "%d", &numVertices);

    // Create an array of linked lists for adjacency list representation
    Node* adjacencyList[MAX_VERTICES] = {NULL};

    // Read the edges and populate the adjacency list
    while (fscanf(file, "%d %d", &vertex1, &vertex2) == 2) {
        if (vertex1 < 0 || vertex1 >= numVertices || vertex2 < 0 || vertex2 >= numVertices) {
            printf("Invalid vertex number(s) detected.\n");
            fclose(file);
            return 1;
        }
        addEdge(adjacencyList, vertex1, vertex2);
    }

    // Close the file
    fclose(file);

    // Perform DFS
    int startVertex;
    printf("Enter the starting vertex for DFS: ");
    scanf("%d", &startVertex);
    if (startVertex < 0 || startVertex >= numVertices) {
        printf("Invalid start vertex.\n");
        return 1;
    }

    dfs(adjacencyList, numVertices, startVertex);

    return 0;
}
\
