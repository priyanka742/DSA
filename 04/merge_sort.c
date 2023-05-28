#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate N random numbers between P and Q and write to a file
void generate_numbers(char *filename, int N, int P, int Q) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        int num = rand() % (Q - P + 1) + P;
        fprintf(fp, "%d\n", num);
    }

    fclose(fp);
}

// Function to read numbers from a file and return a pointer to an array
int* read_numbers(char *filename, int *size) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    int *numbers = malloc(sizeof(int));
    int capacity = 1;
    int i = 0;

    while (fscanf(fp, "%d", &numbers[i]) != EOF) {
        i++;
        if (i == capacity) {
            capacity *= 2;
            numbers = realloc(numbers, capacity * sizeof(int));
        }
    }

    fclose(fp);

    *size = i;

    return numbers;
}

// Function to write sorted numbers to a file
void write_numbers(char *filename, int *numbers, int size) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        fprintf(fp, "%d\n", numbers[i]);
    }

    fclose(fp);
}

// Merge sort algorithm
void merge(int *numbers, int *temp, int left_start, int right_start, int right_end) {
    int left_end = right_start - 1;
    int temp_pos = left_start;
    int num_elements = right_end - left_start + 1;

    while (left_start <= left_end && right_start <= right_end) {
        if (numbers[left_start] < numbers[right_start]) {
            temp[temp_pos++] = numbers[left_start++];
        } else {
            temp[temp_pos++] = numbers[right_start++];
        }
    }

    while (left_start <= left_end) {
        temp[temp_pos++] = numbers[left_start++];
    }

    while (right_start <= right_end) {
        temp[temp_pos++] = numbers[right_start++];
    }

    for (int i = 0; i < num_elements; i++, right_end--) {
        numbers[right_end] = temp[right_end];
    }
}

void merge_sort(int *numbers, int *temp, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = (left + right) / 2;

    merge_sort(numbers, temp, left, mid);
    merge_sort(numbers, temp, mid + 1, right);
    merge(numbers, temp, left, mid + 1, right);
}

// Function to analyze the time required to sort numbers using Merge sort
void time_analysis(int *numbers, int size, int x, char *filename) {
    clock_t start, end;
    double cpu_time_used;

}
