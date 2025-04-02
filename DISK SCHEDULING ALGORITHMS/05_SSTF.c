#include <stdio.h>
#include <stdlib.h>

int findClosestRequest(int head, int requests[], int n, int processed[])
{
    int minDistance = __INT_MAX__;
    int closestRequestIndex = -1;
    for (int i = 0; i < n; i++)
    {
        if (!processed[i])
        {
            int distance = abs(requests[i] - head);
            if (distance < minDistance)
            {
                minDistance = distance;
                closestRequestIndex = i;
            }
        }
    }
    return closestRequestIndex;
}

void SSTF(int requests[], int n, int head)
{
    int processed[n];
    for (int i = 0; i < n; i++)
    {
        processed[i] = 0;
    }

    int totalSeekTime = 0;
    int totalHeadMovement = 0;
    int currentHead = head;

    printf("\nSeek Sequence: %d", currentHead);

    for (int i = 0; i < n; i++)
    {
        int closestRequestIndex = findClosestRequest(currentHead, requests, n, processed);
        processed[closestRequestIndex] = 1;

        int distance = abs(requests[closestRequestIndex] - currentHead);
        totalSeekTime += distance;
        totalHeadMovement += distance;

        currentHead = requests[closestRequestIndex];
        printf(" -> %d", currentHead);
    }

    printf("\nTotal Seek Time: %d", totalSeekTime);
    printf("\nTotal Head Movement: %d cylinders\n", totalHeadMovement);
}

int main()
{
    int n, head;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    SSTF(requests, n, head);

    return 0;
}