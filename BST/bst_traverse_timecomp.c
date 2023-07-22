#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    clock_t start1=clock();
    FILE* preOrderFile = fopen("preorder.txt", "w");
    clock_t end1 =clock();
    double time_taken1 =((double)(end1-start1))/CLOCKS_PER_SEC;
    printf("time taken for preorder :%.6fseconds\n",time_taken1);

    clock_t start2=clock();
    FILE* inOrderFile = fopen("inorder.txt", "w");
    clock_t end2 =clock();
    double time_taken2 =((double)(end2-start2))/CLOCKS_PER_SEC;
    printf("time taken for inorder :%.6fseconds\n",time_taken2);

    clock_t start3=clock();
    FILE* postOrderFile = fopen("postorder.txt", "w");
    clock_t end3 =clock();
    double time_taken3 =((double)(end3-start3))/CLOCKS_PER_SEC;
    printf("time taken for postorder :%.6fseconds\n",time_taken3);


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
