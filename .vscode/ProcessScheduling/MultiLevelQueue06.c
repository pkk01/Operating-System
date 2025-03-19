#include <stdio.h>

#define MAX_PROCESSES 100

struct Process
{
    int pid;             // Process ID
    int burst_time;      // Burst Time
    int waiting_time;    // Waiting Time
    int turnaround_time; // Turnaround Time
    int queue_level;     // Queue Level
};

void calculateTimes(struct Process proc[], int n)
{
    // Calculate waiting time
    proc[0].waiting_time = 0;
    for (int i = 1; i < n; i++)
    {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++)
    {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

void displayResults(struct Process proc[], int n)
{
    float total_waiting = 0, total_turnaround = 0;

    printf("\nProcess\tBurst Time\tQueue Level\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        total_waiting += proc[i].waiting_time;
        total_turnaround += proc[i].turnaround_time;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid,
               proc[i].burst_time,
               proc[i].queue_level,
               proc[i].waiting_time,
               proc[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_waiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);
}

void multiLevelQueue(struct Process proc[], int n)
{
    // Separate processes into different queues based on their queue level
    struct Process queue1[MAX_PROCESSES], queue2[MAX_PROCESSES];
    int n1 = 0, n2 = 0;

    for (int i = 0; i < n; i++)
    {
        if (proc[i].queue_level == 1)
        {
            queue1[n1++] = proc[i];
        }
        else
        {
            queue2[n2++] = proc[i];
        }
    }

    // Calculate times for each queue
    calculateTimes(queue1, n1);
    calculateTimes(queue2, n2);

    // Merge results back into the original array
    for (int i = 0; i < n1; i++)
    {
        proc[i] = queue1[i];
    }
    for (int i = 0; i < n2; i++)
    {
        proc[n1 + i] = queue2[i];
    }
}

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process burst times and queue levels
    for (int i = 0; i < n; i++)
    {
        proc[i].pid = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        printf("Enter queue level for Process %d (1 or 2): ", i + 1);
        scanf("%d", &proc[i].queue_level);
    }

    multiLevelQueue(proc, n);
    displayResults(proc, n);

    return 0;
}