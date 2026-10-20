#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    FILE *file = fopen("input.txt", "w");
    if (!file) {
        printf("Error creating file!\n");
        return 1;
    }

    srand(time(0));  // Seed for random numbers
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", rand() % 100000);  // Generate random numbers up to 99999
    }

    fclose(file);
    printf("input.txt generated successfully with %d numbers!\n", n);
    return 0;
}
