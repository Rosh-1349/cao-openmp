#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 20000

void read_from_file(int arr[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        exit(1);
    }
    for (int i = 0; i < SIZE; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
}

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void parallel_insertion_sort(int arr[], int n, int num_threads) {
    int chunk_size = n / num_threads;
    
    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        int start = thread_id * chunk_size;
        int end = (thread_id == num_threads - 1) ? n : start + chunk_size;

        insertion_sort(arr + start, end - start); 
    }

    for (int i = chunk_size; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int *arr = malloc(SIZE * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    read_from_file(arr, "input.txt");

    double start = omp_get_wtime();
    parallel_insertion_sort(arr, SIZE, 20);
    double end = omp_get_wtime();

    printf("Parallel Execution Time (Insertion Sort): %f seconds\n", end - start);

    free(arr);
    return 0;
}
