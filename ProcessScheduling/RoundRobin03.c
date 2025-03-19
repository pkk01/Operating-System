#include <stdio.h>

struct Process
{
    int pid;             // Process ID
    int burst_time;      // Burst Time
    int remaining_time;  // Remaining Time
    int waiting_time;    // Waiting Time
    int turnaround_time; // Turnaround Time
};

void roundRobin(struct Process proc[], int n, int quantum)
{
    int remaining = n;
    int current_time = 0;

    // Initialize remaining time
    for (int i = 0; i < n; i++)
    {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
    }

    // Process until all processes are completed
    while (remaining > 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (proc[i].remaining_time > 0)
            {
                int execute_time = (proc[i].remaining_time < quantum) ? proc[i].remaining_time : quantum;

                proc[i].remaining_time -= execute_time;
                current_time += execute_time;

                if (proc[i].remaining_time == 0)
                {
                    remaining--;
                    proc[i].turnaround_time = current_time;
                    proc[i].waiting_time = current_time - proc[i].burst_time;
                }
            }
        }
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
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    struct Process proc[n];

    // Input process burst times
    for (int i = 0; i < n; i++)
    {
        proc[i].pid = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
    }

    roundRobin(proc, n, quantum);
    displayResults(proc, n);

    return 0;
}