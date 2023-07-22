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

    // Add an edge from dest to src (assuming undirected graph)
    newNode = createNode(src);
    newNode->next = adjacencyList[dest];
    adjacencyList[dest] = newNode;
}

void bfs(Node* adjacencyList[], int numVertices, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    printf("BFS Traversal: ");

    while (front != rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* current = adjacencyList[currentVertex];
        while (current != NULL) {
            int neighbor = current->vertex;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue[rear++] = neighbor;
            }
            current = current->next;
        }
    }

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

    // Perform BFS
    int startVertex;
    printf("Enter the starting vertex for BFS: ");
    scanf("%d", &startVertex);
    if (startVertex < 0 || startVertex >= numVertices) {
        printf("Invalid start vertex.\n");
        return 1;
    }

    bfs(adjacencyList, numVertices, startVertex);

    return 0;
}
