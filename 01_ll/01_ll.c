#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printList(Node* head) {
    printf("Generated numbers: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void writeToFile(Node* head) {
    FILE* fp = fopen("Input.txt", "w");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    while (head != NULL) {
        fprintf(fp, "%d ", head->data);
        head = head->next;
    }
    fclose(fp);
    printf("Successfully wrote numbers to file.\n");
}

int main() {
    int n, p, q, i;
    Node* head = NULL;

    printf("Enter the number of random numbers to generate: ");
    scanf("%d", &n);
    printf("Enter the range (P Q) of random numbers: ");
    scanf("%d %d", &p, &q);

    srand(time(NULL));
    for (i = 0; i < n; i++) {
        int num = (rand() % (q - p + 1)) + p;
        insertNode(&head, num);
    }

    printList(head);
    writeToFile(head);

    return 0;
}
