#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int n, head, size, seek_count = 0, distance, cur_track;
    int direction;
    printf("Enter the size of the disk: ");
    scanf("%d", &size);
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    sort(arr, n);

    int index;
    for (int i = 0; i < n; i++) {
        if (head < arr[i]) {
            index = i;
            break;
        }
    }

    if (direction == 1) {
        for (int i = index; i < n; i++) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
        for (int i = 0; i < index; i++) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
    } else {
        for (int i = index - 1; i >= 0; i--) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
        for (int i = n - 1; i >= index; i--) {
            cur_track = arr[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
    }

    printf("Total seek operations: %d\n", seek_count);
    return 0;
}