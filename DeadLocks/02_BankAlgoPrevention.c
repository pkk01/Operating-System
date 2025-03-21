// Question: Write a C program to simulate Bankers Algorithm for Deadlock Prevention.

#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES],
                  int alloc[MAX_PROCESSES][MAX_RESOURCES], int P, int R) {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

int isSafe(int processes, int resources, int available[], int max[][MAX_RESOURCES],
           int alloc[][MAX_RESOURCES]) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculateNeed(need, max, alloc, processes, resources);
    
    int finish[MAX_PROCESSES] = {0};
    int safeSeq[MAX_PROCESSES];
    int work[MAX_RESOURCES];
    
    for (int i = 0; i < resources; i++)
        work[i] = available[i];
    
    int count = 0;
    while (count < processes) {
        int found = 0;
        for (int p = 0; p < processes; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < resources; j++)
                    if (need[p][j] > work[j])
                        break;
                
                if (j == resources) {
                    for (int k = 0; k < resources; k++)
                        work[k] += alloc[p][k];
                    
                    safeSeq[count] = p;
                    finish[p] = 1;
                    count++;
                    found = 1;
                }
            }
        }
        if (found == 0)
            return 0;
    }
    
    printf("Safe sequence is: ");
    for (int i = 0; i < processes; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    
    return 1;
}

int main() {
    int processes, resources;
    
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter number of resources: ");
    scanf("%d", &resources);
    
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int alloc[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            scanf("%d", &alloc[i][j]);
    
    printf("Enter maximum matrix:\n");
    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            scanf("%d", &max[i][j]);
    
    printf("Enter available resources:\n");
    for (int i = 0; i < resources; i++)
        scanf("%d", &available[i]);
    
    if (isSafe(processes, resources, available, max, alloc))
        printf("System is in safe state.\n");
    else
        printf("System is in unsafe state!\n");
    
    return 0;
}