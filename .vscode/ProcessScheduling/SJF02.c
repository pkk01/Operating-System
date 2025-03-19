#include <stdio.h>

// Structure to store process information
struct Process
{
    int pid; // Process ID
    int bt;  // Burst Time
    int wt;  // Waiting Time
    int tat; // Turnaround Time
};

// Function to sort processes by burst time
void sortByBurstTime(struct Process proc[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (proc[j].bt > proc[j + 1].bt)
            {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

void calculateTimes(struct Process proc[], int n)
{
    // First process has 0 waiting time
    proc[0].wt = 0;

    // Calculate waiting time
    for (int i = 1; i < n; i++)
    {
        proc[i].wt = proc[i - 1].bt + proc[i - 1].wt;
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++)
    {
        proc[i].tat = proc[i].bt + proc[i].wt;
    }
}

void displayResults(struct Process proc[], int n)
{
    float total_wt = 0, total_tat = 0;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++)
    {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, proc[i].wt, proc[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input burst time for each process
    for (int i = 0; i < n; i++)
    {
        proc[i].pid = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &proc[i].bt);
    }

    // Sort processes based on burst time
    sortByBurstTime(proc, n);

    // Calculate waiting and turnaround times
    calculateTimes(proc, n);

    // Display results
    displayResults(proc, n);

    return 0;
}