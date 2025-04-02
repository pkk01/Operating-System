#include <stdio.h>
#include <stdlib.h>

void FCFS(int requests[], int n, int head)
{
    int seek_sequence[n + 1];
    int seek_count = 0;
    int total_head_movement = 0;
    int distance, cur_track;

    seek_sequence[0] = head;

    for (int i = 0; i < n; i++)
    {
        cur_track = requests[i];
        distance = abs(cur_track - head);
        seek_count += distance;
        total_head_movement += distance;
        head = cur_track;
        seek_sequence[i + 1] = cur_track;
    }

    printf("\nTotal number of seek operations: %d", seek_count);
    printf("\nTotal head movement: %d cylinders", total_head_movement);
    printf("\nSeek Sequence is:\n");
    for (int i = 0; i <= n; i++)
    {
        printf("%d ", seek_sequence[i]);
    }
    printf("\n");
}

int main()
{
    int n, head;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    FCFS(requests, n, head);

    return 0;
}