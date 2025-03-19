#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int n1, n2, i;

    // Initial memory allocation
    printf("Enter the initial number of elements: ");
    scanf("%d", &n1);

    ptr = (int*)malloc(n1 * sizeof(int));

    if (ptr == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    } else {
        printf("Memory successfully allocated using malloc.\n");

        // Get the elements of the array
        for (i = 0; i < n1; ++i) {
            ptr[i] = i + 1;
        }

        // Print the elements of the array
        printf("The elements of the array are: ");
        for (i = 0; i < n1; ++i) {
            printf("%d ", ptr[i]);
        }

        // Reallocate the memory
        printf("\n\nEnter the new number of elements: ");
        scanf("%d", &n2);

        ptr = realloc(ptr, n2 * sizeof(int));

        if (ptr == NULL) {
            printf("Memory not reallocated.\n");
            exit(0);
        } else {
            printf("Memory successfully reallocated using realloc.\n");

            // Get the new elements of the array
            for (i = n1; i < n2; ++i) {
                ptr[i] = i + 1;
            }

            // Print the new elements of the array
            printf("The elements of the array are: ");
            for (i = 0; i < n2; ++i) {
                printf("%d ", ptr[i]);
            }
        }
    }

    // Free the allocated memory
    free(ptr);

    return 0;
}