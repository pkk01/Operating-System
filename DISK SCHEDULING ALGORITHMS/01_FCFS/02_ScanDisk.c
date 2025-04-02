#include <stdio.h>
#include <stdlib.h>

void scanDisk(int arr[], int n, int head, int direction)
{
    int seek_count = 0;
    int total_head_movement = 0;
    int distance, cur_track;
    int size = n + 1;
    int seek_sequence[size];
    int left[n], right[n];
    int left_size = 0, right_size = 0;

    // Appending end values which has to be visited before reversing the direction
    if (direction == 0)
    {
        left[left_size++] = 0;
    }
    else if (direction == 1)
    {
        right[right_size++] = 199;
    }

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < head)
        {
            left[left_size++] = arr[i];
        }
        if (arr[i] > head)
        {
            right[right_size++] = arr[i];
        }
    }

    // Sorting left and right arrays
    qsort(left, left_size, sizeof(int), cmpfunc);
    qsort(right, right_size, sizeof(int), cmpfunc);

    // Run the while loop two times.
    // One by one scanning right and left side of the head
    int run = 2;
    int index = 0;
    while (run--)
    {
        if (direction == 0)
        {
            for (int i = left_size - 1; i >= 0; i--)
            {
                cur_track = left[i];
                seek_sequence[index++] = cur_track;
                distance = abs(cur_track - head);
                seek_count += distance;
                total_head_movement += distance;
                head = cur_track;
            }
            direction = 1;
        }
        else if (direction == 1)
        {
            for (int i = 0; i < right_size; i++)
            {
                cur_track = right[i];
                seek_sequence[index++] = cur_track;
                distance = abs(cur_track - head);
                seek_count += distance;
                total_head_movement += distance;
                head = cur_track;
            }
            direction = 0;
        }
    }

    printf("Total seek operations: %d\n", seek_count);
    printf("Total head movement: %d cylinders\n", total_head_movement);
    printf("Seek Sequence is:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", seek_sequence[i]);
    }
    printf("\n");
}

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n, head, direction;
    printf("Enter the size of request array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the request array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    scanDisk(arr, n, head, direction);

    return 0;
}