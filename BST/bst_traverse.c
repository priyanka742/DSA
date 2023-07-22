#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insertNode(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }

    return root;
}

void preOrderTraversal(struct Node* root, FILE* file) {
    if (root != NULL) {
        fprintf(file, "%d ", root->data);
        preOrderTraversal(root->left, file);
        preOrderTraversal(root->right, file);
    }
}

void inOrderTraversal(struct Node* root, FILE* file) {
    if (root != NULL) {
        inOrderTraversal(root->left, file);
        fprintf(file, "%d ", root->data);
        inOrderTraversal(root->right, file);
    }
}

void postOrderTraversal(struct Node* root, FILE* file) {
    if (root != NULL) {
        postOrderTraversal(root->left, file);
        postOrderTraversal(root->right, file);
        fprintf(file, "%d ", root->data);
    }
}

void createAndPrintSortedFiles(char* inputFileName) {
    FILE* inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Failed to open the input file.\n");
        return;
    }

    struct Node* root = NULL;
    int value;

    while (fscanf(inputFile, "%d", &value) != EOF) {
        root = insertNode(root, value);
    }

    fclose(inputFile);

    FILE* preOrderFile = fopen("preorder.txt", "w");
    FILE* inOrderFile = fopen("inorder.txt", "w");
    FILE* postOrderFile = fopen("postorder.txt", "w");

    if (preOrderFile == NULL || inOrderFile == NULL || postOrderFile == NULL) {
        printf("Failed to create the output files.\n");
        return;
    }

    preOrderTraversal(root, preOrderFile);
    inOrderTraversal(root, inOrderFile);
    postOrderTraversal(root, postOrderFile);

    fclose(preOrderFile);
    fclose(inOrderFile);
    fclose(postOrderFile);

    printf("Files created successfully!\n");
}

int main() {
    char* inputFileName = "random_numbers.txt";
    createAndPrintSortedFiles(inputFileName);
    return 0;
}
