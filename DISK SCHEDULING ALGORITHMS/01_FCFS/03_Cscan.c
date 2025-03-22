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
    int n, head, size, total_movement = 0;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int requests[n + 1];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the total disk size: ");
    scanf("%d", &size);

    requests[n] = head;
    sort(requests, n + 1);

    int index;
    for (int i = 0; i < n + 1; i++) {
        if (requests[i] == head) {
            index = i;
            break;
        }
    }

    printf("Seek Sequence: ");
    for (int i = index; i < n + 1; i++) {
        printf("%d ", requests[i]);
        if (i != index) {
            total_movement += abs(requests[i] - requests[i - 1]);
        }
    }
    total_movement += abs(size - 1 - requests[n]);
    total_movement += abs(size - 1 - requests[0]);
    for (int i = 0; i < index; i++) {
        printf("%d ", requests[i]);
        if (i != 0) {
            total_movement += abs(requests[i] - requests[i - 1]);
        }
    }

    printf("\nTotal head movement: %d\n", total_movement);
    return 0;
}