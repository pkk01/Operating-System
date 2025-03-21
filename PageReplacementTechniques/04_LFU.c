#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int page;
    int count;
    int time;
} PageFrame;

void LFU(int pages[], int n, int capacity) {
    PageFrame frames[capacity];
    int i, j, k, pageFaults = 0, time = 0;

    for (i = 0; i < capacity; i++) {
        frames[i].page = -1;
        frames[i].count = 0;
        frames[i].time = 0;
    }

    for (i = 0; i < n; i++) {
        int found = 0;
        for (j = 0; j < capacity; j++) {
            if (frames[j].page == pages[i]) {
                frames[j].count++;
                frames[j].time = time++;
                found = 1;
                break;
            }
        }

        if (!found) {
            int lfuIndex = 0;
            for (j = 1; j < capacity; j++) {
                if (frames[j].count < frames[lfuIndex].count ||
                    (frames[j].count == frames[lfuIndex].count && frames[j].time < frames[lfuIndex].time)) {
                    lfuIndex = j;
                }
            }

            frames[lfuIndex].page = pages[i];
            frames[lfuIndex].count = 1;
            frames[lfuIndex].time = time++;
            pageFaults++;
        }

        printf("Frame status after accessing page %d: ", pages[i]);
        for (k = 0; k < capacity; k++) {
            if (frames[k].page != -1) {
                printf("%d ", frames[k].page);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("Total page faults: %d\n", pageFaults);
}

int main() {
    int n, capacity, i;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference sequence: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    LFU(pages, n, capacity);

    return 0;
}