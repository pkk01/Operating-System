#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 100

struct Process
{
    int pid;             // Process ID
    int burst_time;      // Burst Time
    int waiting_time;    // Waiting Time
    int turnaround_time; // Turnaround Time
    int tickets;         // Number of tickets
};

void calculateTimes(struct Process proc[], int n)
{
    int current_time = 0;
    int completed = 0;
    int total_tickets = 0;

    // Calculate total number of tickets
    for (int i = 0; i < n; i++)
    {
        total_tickets += proc[i].tickets;
    }

    while (completed < n)
    {
        // Generate a random ticket number
        int winning_ticket = rand() % total_tickets + 1;
        int ticket_sum = 0;

        // Find the winning process
        for (int i = 0; i < n; i++)
        {
            ticket_sum += proc[i].tickets;
            if (ticket_sum >= winning_ticket && proc[i].burst_time > 0)
            {
                // Execute the winning process
                current_time += proc[i].burst_time;
                proc[i].turnaround_time = current_time;
                proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
                proc[i].burst_time = 0;
                completed++;
                break;
            }
        }
    }
}

void displayResults(struct Process proc[], int n)
{
    float total_waiting = 0, total_turnaround = 0;

    printf("\nProcess\tBurst Time\tTickets\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        total_waiting += proc[i].waiting_time;
        total_turnaround += proc[i].turnaround_time;
        printf("%d\t%d\t\t%d\t%d\t\t%d\n",
               proc[i].pid,
               proc[i].burst_time,
               proc[i].tickets,
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

    // Input process burst times and number of tickets
    for (int i = 0; i < n; i++)
    {
        proc[i].pid = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        printf("Enter number of tickets for Process %d: ", i + 1);
        scanf("%d", &proc[i].tickets);
    }

    // Seed the random number generator
    srand(time(0));

    calculateTimes(proc, n);
    displayResults(proc, n);

    return 0;
}