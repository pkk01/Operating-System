#include <stdio.h>

#define MAX_PARTITIONS 10
#define MAX_PROCESSES 10

typedef struct {
    int size;
    int isOccupied;
    int processId;
} Partition;

typedef struct {
    int id;
    int size;
} Process;

void allocateMemory(Partition partitions[], int partitionCount, Process processes[], int processCount) {
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < partitionCount; j++) {
            if (!partitions[j].isOccupied && partitions[j].size >= processes[i].size) {
                partitions[j].isOccupied = 1;
                partitions[j].processId = processes[i].id;
                printf("Process %d allocated to partition %d\n", processes[i].id, j);
                break;
            }
        }
    }
}

void displayMemory(Partition partitions[], int partitionCount) {
    printf("\nPartition Status:\n");
    for (int i = 0; i < partitionCount; i++) {
        if (partitions[i].isOccupied) {
            printf("Partition %d: Occupied by Process %d\n", i, partitions[i].processId);
        } else {
            printf("Partition %d: Free\n", i);
        }
    }
}

int main() {
    Partition partitions[MAX_PARTITIONS];
    Process processes[MAX_PROCESSES];
    int partitionCount, processCount;

    printf("Enter the number of partitions: ");
    scanf("%d", &partitionCount);
    for (int i = 0; i < partitionCount; i++) {
        printf("Enter size of partition %d: ", i);
        scanf("%d", &partitions[i].size);
        partitions[i].isOccupied = 0;
        partitions[i].processId = -1;
    }

    printf("Enter the number of processes: ");
    scanf("%d", &processCount);
    for (int i = 0; i < processCount; i++) {
        printf("Enter size of process %d: ", i);
        scanf("%d", &processes[i].size);
        processes[i].id = i;
    }

    allocateMemory(partitions, partitionCount, processes, processCount);
    displayMemory(partitions, partitionCount);

    return 0;
}