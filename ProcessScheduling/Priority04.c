#include <stdio.h>

struct Process
{
    int pid;             // Process ID
    int burst_time;      // Burst Time
    int priority;        // Priority
    int waiting_time;    // Waiting Time
    int turnaround_time; // Turnaround Time
};

// Function to sort processes by priority
void sortByPriority(struct Process proc[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (proc[j].priority > proc[j + 1].priority)
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
    proc[0].waiting_time = 0;

    // Calculate waiting time
    for (int i = 1; i < n; i++)
    {
        proc[i].waiting_time = proc[i - 1].burst_time + proc[i - 1].waiting_time;
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++)
    {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

void displayResults(struct Process proc[], int n)
{
    float total_waiting = 0, total_turnaround = 0;

    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        total_waiting += proc[i].waiting_time;
        total_turnaround += proc[i].turnaround_time;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid,
               proc[i].burst_time,
               proc[i].priority,
               proc[i].waiting_time,
               proc[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_waiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);
}

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process burst times and priorities
    for (int i = 0; i < n; i++)
    {
        proc[i].pid = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &proc[i].priority);
    }

    // Sort processes based on priority
    sortByPriority(proc, n);

    // Calculate waiting and turnaround times
    calculateTimes(proc, n);

    // Display results
    displayResults(proc, n);

    return 0;
}