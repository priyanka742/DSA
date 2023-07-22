#include <stdio.h>
#include <stdlib.h>

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

void printAdjacencyList(Node* adjacencyList[], int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        printf("Adjacency list of vertex %d: ", i);
        Node* current = adjacencyList[i];
        while (current != NULL) {
            printf("%d ", current->vertex);
            current = current->next;
        }
        printf("\n");
    }
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

    // Print the adjacency list
    printf("Adjacency List:\n");
    printAdjacencyList(adjacencyList, numVertices);

    return 0;
}
