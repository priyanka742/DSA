#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

int main() {
    FILE *file;
    char filename[100];
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES] = {0};
    int numVertices, vertex1, vertex2;

    // Open the file
    printf("Enter the filename: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    if (file == NULL)
        {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Read the number of vertices from the file
    fscanf(file, "%d", &numVertices);

    // Read the edges and populate the adjacency matrix
    while (fscanf(file, "%d %d", &vertex1, &vertex2) == 2) {
        if (vertex1 < 0 || vertex1 >= numVertices || vertex2 < 0 || vertex2 >= numVertices) {
            printf("Invalid vertex number(s) detected.\n");
            fclose(file);
            return 1;
        }
        adjacencyMatrix[vertex1][vertex2] = 1;
        adjacencyMatrix[vertex2][vertex1] = 1; // assuming an undirected graph
    }

    // Close the file
    fclose(file);

    // Print the adjacency matrix
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
