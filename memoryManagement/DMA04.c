#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int n, i;

    // Get the number of elements for the array
    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Dynamically allocate memory using malloc()
    ptr = (int*)malloc(n * sizeof(int));

    // Check if the memory has been successfully allocated by malloc or not
    if (ptr == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    } else {
        // Memory has been successfully allocated
        printf("Memory successfully allocated using malloc.\n");

        // Get the elements of the array
        printf("Enter elements of the array: ");
        for (i = 0; i < n; ++i) {
            scanf("%d", &ptr[i]);
        }

        // Print the elements of the array
        printf("The elements of the array are: ");
        for (i = 0; i < n; ++i) {
            printf("%d ", ptr[i]);
        }

        // Free the allocated memory
        free(ptr);
        printf("\nMemory successfully freed.\n");
    }

    return 0;
}