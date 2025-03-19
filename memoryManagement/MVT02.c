#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int size;
    int allocated;
    int process_id;
} Partition;

void allocate_memory(Partition partitions[], int n, int process_id, int process_size) {
    for (int i = 0; i < n; i++) {
        if (!partitions[i].allocated && partitions[i].size >= process_size) {
            partitions[i].allocated = 1;
            partitions[i].process_id = process_id;
            printf("Process %d allocated to partition %d\n", process_id, i);
            return;
        }
    }
    printf("Process %d could not be allocated\n", process_id);
}

void deallocate_memory(Partition partitions[], int n, int process_id) {
    for (int i = 0; i < n; i++) {
        if (partitions[i].allocated && partitions[i].process_id == process_id) {
            partitions[i].allocated = 0;
            partitions[i].process_id = -1;
            printf("Process %d deallocated from partition %d\n", process_id, i);
            return;
        }
    }
    printf("Process %d not found\n", process_id);
}

void display_partitions(Partition partitions[], int n) {
    printf("Partition\tSize\tAllocated\tProcess ID\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t%d\t\t%d\n", i, partitions[i].size, partitions[i].allocated, partitions[i].process_id);
    }
}

int main() {
    int n, choice, process_id, process_size;
    Partition partitions[MAX];

    printf("Enter the number of partitions: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter size of partition %d: ", i);
        scanf("%d", &partitions[i].size);
        partitions[i].allocated = 0;
        partitions[i].process_id = -1;
    }

    while (1) {
        printf("\n1. Allocate Memory\n2. Deallocate Memory\n3. Display Partitions\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter process ID: ");
                scanf("%d", &process_id);
                printf("Enter process size: ");
                scanf("%d", &process_size);
                allocate_memory(partitions, n, process_id, process_size);
                break;
            case 2:
                printf("Enter process ID to deallocate: ");
                scanf("%d", &process_id);
                deallocate_memory(partitions, n, process_id);
                break;
            case 3:
                display_partitions(partitions, n);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}