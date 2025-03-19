#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

struct Process
{
    int pid;             // Process ID
    int burst_time;      // Burst Time
    int remaining_time;  // Remaining Time
    int waiting_time;    // Waiting Time
    int turnaround_time; // Turnaround Time
    int queue_level;     // Current Queue Level
};

void executeProcess(struct Process *proc, int quantum, int *current_time, int *remaining)
{
    int execute_time = (proc->remaining_time < quantum) ? proc->remaining_time : quantum;
    proc->remaining_time -= execute_time;
    *current_time += execute_time;

    if (proc->remaining_time == 0)
    {
        (*remaining)--;
        proc->turnaround_time = *current_time;
        proc->waiting_time = proc->turnaround_time - proc->burst_time;
    }
    else
    {
        proc->queue_level++;
    }
}

void multiLevelFeedbackQueue(struct Process proc[], int n, int quantum1, int quantum2)
{
    int remaining = n;
    int current_time = 0;

    // Initialize remaining time and queue level
    for (int i = 0; i < n; i++)
    {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
        proc[i].queue_level = 0;
    }

    // Process until all processes are completed
    while (remaining > 0)
    {
        bool executed = false;
        for (int i = 0; i < n; i++)
        {
            if (proc[i].remaining_time > 0)
            {
                if (proc[i].queue_level == 0)
                {
                    executeProcess(&proc[i], quantum1, &current_time, &remaining);
                }
                else if (proc[i].queue_level == 1)
                {
                    executeProcess(&proc[i], quantum2, &current_time, &remaining);
                }
                else
                {
                    executeProcess(&proc[i], proc[i].remaining_time, &current_time, &remaining);
                }
                executed = true;
            }
        }
        if (!executed)
            break; // If no process was executed, break the loop
    }
}

void displayResults(struct Process proc[], int n)
{
    float total_waiting = 0, total_turnaround = 0;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        total_waiting += proc[i].waiting_time;
        total_turnaround += proc[i].turnaround_time;
        printf("%d\t%d\t\t%d\t\t%d\n",
               proc[i].pid,
               proc[i].burst_time,
               proc[i].waiting_time,
               proc[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_waiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);
}

int main()
{
    int n, quantum1, quantum2;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process burst times
    for (int i = 0; i < n; i++)
    {
        proc[i].pid = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
    }

    printf("Enter time quantum for Queue 1: ");
    scanf("%d", &quantum1);

    printf("Enter time quantum for Queue 2: ");
    scanf("%d", &quantum2);

    multiLevelFeedbackQueue(proc, n, quantum1, quantum2);
    displayResults(proc, n);

    return 0;
}