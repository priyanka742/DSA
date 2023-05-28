#include <stdio.h>
#include<time.h>

// Function to swap two integers
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to perform selection sort on an array
void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    clock_t start = clock();
    //printf("%d",n);
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
    clock_t end = clock();
    double time_taken =((double)(end-start))/CLOCKS_PER_SEC;
printf("time taken to sort :%.6fseconds\n",time_taken);

}

int main() {
    FILE *inputFile, *outputFile;
    int arr[10000], n, i;
 printf("enter the numbers that need to be sorted :");
 scanf("%d",&n);
    // Open input file for reading
    inputFile = fopen("random_numbers.txt", "r");
    if (inputFile == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }

    // Read elements from input file
    //fscanf(inputFile, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(inputFile, "%d", &arr[i]);
    }

    // Close input file
    fclose(inputFile);

    // Perform selection sort on the array
    selectionSort(arr, n);

    // Open output file for writing
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Failed to open output file.\n");
        return 1;
    }

    // Write sorted elements to output file
    fprintf(outputFile, "%d\n", n);
    for (i = 0; i < n; i++) {
        fprintf(outputFile, "%d ", arr[i]);
    }

    // Close output file
    fclose(outputFile);

    printf("Sorted elements have been written to output file.\n");

    return 0;
}

