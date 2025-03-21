#include <stdio.h>

// Function prototypes
void initializeValues(int processes, int resources, int available[], int maximum[][10], 
                     int allocation[][10], int need[][10]);
void calculateNeed(int processes, int resources, int need[][10], 
                  int maximum[][10], int allocation[][10]);
int isSafeState(int processes, int resources, int available[], int need[][10], 
                int allocation[][10], int safeSequence[]);
void printMatrix(int processes, int resources, int matrix[][10], const char* name);

int main() {
    int processes, resources;
    int available[10], safeSequence[10];
    int maximum[10][10], allocation[10][10], need[10][10];
    
    // Get number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter number of resources: ");
    scanf("%d", &resources);
    
    // Initialize all matrices and vectors
    initializeValues(processes, resources, available, maximum, allocation, need);
    
    // Calculate Need matrix
    calculateNeed(processes, resources, need, maximum, allocation);
    
    // Print all matrices
    printf("\nInitial System State:\n");
    printMatrix(processes, resources, allocation, "Allocation Matrix");
    printMatrix(processes, resources, maximum, "Maximum Matrix");
    printMatrix(processes, resources, need, "Need Matrix");
    
    printf("\nAvailable Resources: ");
    for(int i = 0; i < resources; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");
    
    // Check if system is in safe state
    if(isSafeState(processes, resources, available, need, allocation, safeSequence)) {
        printf("\nSystem is in SAFE state.\nSafe sequence is: ");
        for(int i = 0; i < processes; i++) {
            printf("P%d ", safeSequence[i]);
            if(i < processes - 1) printf("-> ");
        }
        printf("\n");
    } else {
        printf("\nSystem is in UNSAFE state!\n");
    }
    
    return 0;
}

void initializeValues(int processes, int resources, int available[], int maximum[][10], 
                     int allocation[][10], int need[][10]) {
    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < resources; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &available[i]);
    }
    
    printf("\nEnter Maximum Matrix:\n");
    for(int i = 0; i < processes; i++) {
        printf("For Process %d: ", i);
        for(int j = 0; j < resources; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }
    
    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < processes; i++) {
        printf("For Process %d: ", i);
        for(int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
}

void calculateNeed(int processes, int resources, int need[][10], 
                  int maximum[][10], int allocation[][10]) {
    for(int i = 0; i < processes; i++) {
        for(int j = 0; j < resources; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

int isSafeState(int processes, int resources, int available[], int need[][10], 
                int allocation[][10], int safeSequence[]) {
    int work[10], finish[10];
    
    // Initialize work and finish arrays
    for(int i = 0; i < resources; i++)
        work[i] = available[i];
    for(int i = 0; i < processes; i++)
        finish[i] = 0;
        
    int count = 0;
    while(count < processes) {
        int found = 0;
        for(int i = 0; i < processes; i++) {
            if(finish[i] == 0) {
                int j;
                for(j = 0; j < resources; j++) {
                    if(need[i][j] > work[j])
                        break;
                }
                if(j == resources) {
                    for(int k = 0; k < resources; k++)
                        work[k] += allocation[i][k];
                    safeSequence[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }
        if(found == 0)
            return 0;
    }
    return 1;
}

void printMatrix(int processes, int resources, int matrix[][10], const char* name) {
    printf("\n%s:\n", name);
    for(int i = 0; i < processes; i++) {
        for(int j = 0; j < resources; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}